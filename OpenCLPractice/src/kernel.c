__kernel void VecProcess(__global const int *A, __global const int *B, __global int *C)
{
	int i = get_global_id(0);
	C[i] = A[i]*2 + B[i] - 5;
}