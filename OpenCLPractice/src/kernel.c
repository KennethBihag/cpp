__kernel void VecProcess(__global const int *A, __global const int *B, __global int *C)
{
    int i = get_global_id(0);
    int j = get_global_id(1);
    size_t w = get_global_size(0);
    C[j*w + i] = A[j*w+i]*2 + B[j*w+i] - 5;
}

__kernel void ReductionSum(__global const int *A, __global long long *B, __local long long *T)
{
    size_t locSz = get_local_size(0);
    size_t locPos = get_local_id(0);
    int gpId = get_group_id(0);
    int gOff = gpId * locSz;
    T[locPos] = A[gOff + locPos];

    int gap = 2;
    barrier(CLK_LOCAL_MEM_FENCE);
    while(gap <= locSz)
    {
        int subG = locPos/gap;
        int posToKp = subG*gap + gap-1;
        if(locPos == posToKp)
            T[locPos] += T[locPos-gap/2];
        gap *= 2;
        barrier(CLK_LOCAL_MEM_FENCE);
    }
    if(locPos == locSz-1)
        B[gpId] = T[locPos];
}