__kernel void VecProcess(__global const int *A, __global const int *B, __global int *C)
{
    int i = get_global_id(0);
    int j = get_global_id(1);
    size_t w = get_global_size(0);
    C[j*w + i] = A[j*w+i]*2 + B[j*w+i] - 5;
}