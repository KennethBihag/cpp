#include "pch.h"

using namespace std;

#define QRY_ITEM(k) {k,#k}

cl_int CL_err = CL_SUCCESS;
constexpr unsigned long gsz = 1024*1024*1052/sizeof(int);
constexpr unsigned long gszSz = gsz * sizeof(int);
shared_ptr<int[]> A(new int[gsz]), B(new int[gsz]), C(new int[gsz]);

#define AssertCL() \
assert(CL_err == CL_SUCCESS); \
if(CL_err != CL_SUCCESS) \
    cerr << "CL_err = " << CL_err << endl;

static string FileToText(string path) {
    ifstream kernelFile(path);
    if(!kernelFile)
        return "";
    stringstream ssRet;
    while (kernelFile) {
        constexpr int sz = 128;
        char buff[sz];
        kernelFile.getline(buff, sz);
        ssRet << string(buff) << "\n";
    }

    return ssRet.str();
}

static inline void VecProcessCpu() {
    int *A = ::A.get(), *B = ::B.get();
    int *C = ::C.get();
    for (unsigned long i = 0; i < gsz; i++) {
        C[i] = A[i] * 2 + B[i] - 5;
    }
}

static inline double BenchMark(clock_t& cStart) {
    clock_t cEnd = clock();
    clock_t cDur = cEnd - cStart;
    double sDur = double(cDur) / CLOCKS_PER_SEC;
    return sDur;
}

template<typename T, size_t N>
static inline void PrintIntVecElems(T(&idxs)[N], int *arr){
    for (auto &i : idxs)
        cout << arr[i] << " ";
}

template<typename T, size_t N>
static inline array<int, N> GetIntVecElems(T(&idxs)[N], int *arr){
    array<int, N> ret;
    for(size_t i=0; i<N; ++i)
        ret[i] = arr[idxs[i]];
    return ret;
}

int main()
{
    printf("Elements per array: %lu\n", gsz);
    printf("MB per array: %lf\n", double(gszSz) / (1024 * 1024));
    printf("Total MB: %.2lf\n", double(gszSz * 3) / (1024 * 1024));
    string kernelSrc = FileToText("src/kernel.c");
// OPENCL QUERIES
    cl_uint numPlatforms;
    vector<cl_platform_id> platforms;
    CL_err = clGetPlatformIDs(0, NULL, &numPlatforms); AssertCL();
    platforms.assign(numPlatforms, cl_platform_id{});
    CL_err = clGetPlatformIDs(numPlatforms, platforms.data(), NULL); AssertCL();

    string s;
    array queries{
            CL_PLATFORM_NAME,
            CL_PLATFORM_VERSION,
            CL_PLATFORM_VENDOR,
            CL_PLATFORM_PROFILE,
    };
    printf("Platform 1:\n");
    for (auto& q : queries) {
        s = "";
        s.resize(256);

        CL_err = clGetPlatformInfo(
            platforms[0],
            q,
            s.size(),
            s.data(),
            NULL
        ); AssertCL();
        if (s.empty())
            s.assign("N/A");
        printf("\t%s\n", s.c_str());
    }

    cl_uint numDev;
    int devTyp = CL_DEVICE_TYPE_GPU;
    CL_err = clGetDeviceIDs(platforms[0], devTyp, 0, NULL, &numDev);
    AssertCL();
    vector<cl_device_id> devIds((size_t)numDev, cl_device_id());
    CL_err = clGetDeviceIDs(platforms[0], devTyp, 1, devIds.data(), NULL); AssertCL();
    queries = {CL_DEVICE_NAME, CL_DEVICE_GLOBAL_MEM_SIZE};
    printf("Device 1:\n");
    s = "", s.resize(256);
    CL_err = clGetDeviceInfo(devIds[0], CL_DEVICE_NAME, s.size(), s.data(), NULL); AssertCL();
    printf("\tName: %s\n", s.c_str());

    map<int, string> numQrs{
        QRY_ITEM(CL_DEVICE_MAX_COMPUTE_UNITS),
        QRY_ITEM(CL_DEVICE_GLOBAL_MEM_SIZE),
        QRY_ITEM(CL_DEVICE_MAX_WORK_ITEM_DIMENSIONS),
        QRY_ITEM(CL_DEVICE_GLOBAL_MEM_CACHELINE_SIZE),
        QRY_ITEM(CL_DEVICE_LOCAL_MEM_SIZE),
        QRY_ITEM(CL_DEVICE_MAX_MEM_ALLOC_SIZE)
    };
    for (auto& p : numQrs) {
        cl_ulong val = 0;
        CL_err = clGetDeviceInfo(devIds[0], p.first, sizeof(val), &val, NULL); AssertCL();
        printf("\t%-40s: %-16lu", p.second.c_str(), val);
        if (p.second.find("_MEM_") != string::npos) {
            double memMb = val;
            printf(" : %-12.2lfKB : %8.2lfMB", memMb/pow(2,10), memMb/pow(2,20));
        }
        printf("\n");
    }
    std::string sep(16, '*');
    printf("%s", sep.c_str());
    printf("\n");

#if true
// HOST
//// RAW DATA SETUP
    clock_t cStart = clock();

    for (unsigned long i = 0; i < gsz; ++i) {
        unsigned long j = 2*i;
        A[i] = j;
        B[i] = j+1;
    }
    //memset(C.get(), -1, gsz * sizeof(int));
    double sDur = BenchMark(cStart);
    printf("Initialized arrays in %.4lfs\n", sDur);
//// COMPUTE
    cStart = clock();
    VecProcessCpu();
    sDur = BenchMark(cStart);
    printf("CPU: Added arrays in %.4lfs\n", sDur);

    default_random_engine re;
    uniform_int_distribution<unsigned long> dist(0, gsz-1);
    unsigned long rndIdx[5];
    for(auto &i : rndIdx)
        i = dist(re);
    auto cpuAns = GetIntVecElems(rndIdx, C.get());
    memset(C.get(), 0, gszSz);
// GPU
//// CONTEXT
#ifdef _WIN32
#pragma warning(disable:4996)
#endif
    cl_context clCtxt = clCreateContext(NULL, 1, devIds.data(), NULL, NULL, &CL_err); AssertCL();
    cl_command_queue clCmdQue = clCreateCommandQueue(clCtxt, devIds[0], (cl_command_queue_properties)0, &CL_err); AssertCL();
#ifdef _WIN32
    #pragma warning(enable:4996)
#endif
//// DATA
////// CREATE
    cl_mem gpuA, gpuB, gpuC;
    gpuA = clCreateBuffer(clCtxt, CL_MEM_READ_ONLY, gszSz, NULL, &CL_err); AssertCL();
    gpuB = clCreateBuffer(clCtxt, CL_MEM_READ_ONLY, gszSz, NULL, &CL_err); AssertCL();
    gpuC = clCreateBuffer(clCtxt, CL_MEM_WRITE_ONLY, gszSz, NULL, &CL_err); AssertCL();
////// COPY
    CL_err = clEnqueueWriteBuffer(clCmdQue, gpuA, CL_FALSE, 0, gszSz, A.get(), 0, NULL, NULL); AssertCL();
    CL_err = clEnqueueWriteBuffer(clCmdQue, gpuB, CL_FALSE, 0, gszSz, B.get(), 0, NULL, NULL); AssertCL();
    cStart = clock();
    clFinish(clCmdQue);
    sDur = BenchMark(cStart);
    printf("GPU: Copied data in %.4lfs\n", sDur);
//// KERNEL PROGRAM SETUP
    const char *kernelSrcStr = kernelSrc.c_str();
    const char **kernelSources = &kernelSrcStr;
    cl_program clProg = clCreateProgramWithSource(clCtxt, 1, kernelSources, NULL, &CL_err); AssertCL();
    CL_err = clBuildProgram(clProg, 1, devIds.data(), NULL, NULL, NULL); AssertCL();
    cl_kernel clKrnl = clCreateKernel(clProg, "VecProcess", &CL_err); AssertCL();
    CL_err = clSetKernelArg(clKrnl, 0, sizeof(gpuA), &gpuA); AssertCL();
    CL_err = clSetKernelArg(clKrnl, 1, sizeof(gpuB), &gpuB); AssertCL();
    CL_err = clSetKernelArg(clKrnl, 2, sizeof(gpuC), &gpuC); AssertCL();
//// EXECUTE
    size_t glWSzs[]{512, 538624}, lcWSzs[]{16, 32};
    CL_err = clEnqueueNDRangeKernel(clCmdQue, clKrnl, 2, NULL, glWSzs, lcWSzs, 0, NULL, NULL); AssertCL();
    cStart = clock();
    clFinish(clCmdQue);
    sDur = BenchMark(cStart);
    printf("GPU: Processed arrays in %.4lfs\n", sDur);
//// READ BACK
    CL_err = clEnqueueReadBuffer(clCmdQue, gpuC, CL_TRUE, 0, gszSz, C.get(), 0, NULL, NULL); AssertCL();
    auto gpuAns = GetIntVecElems(rndIdx, C.get());
    auto res = cpuAns == gpuAns;
    assert(res);

// CLEANUP
    clReleaseKernel(clKrnl);
    clReleaseProgram(clProg);
    clReleaseMemObject(gpuC), clReleaseMemObject(gpuB), clReleaseMemObject(gpuA);
    clReleaseCommandQueue(clCmdQue);
    clReleaseContext(clCtxt);
#endif

    printf("\n*** END ***\n");

    return 0;
}