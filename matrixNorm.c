/* Matrix normalization.
 * Compile with "gcc matrixNorm.c"
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <math.h>

/* Program Parameters */
#define N 6000  /* Matrix size */

/* Matrices */
float A[N][N], B[N][N];


/* Initialize A and B*/
void initialize_inputs() {
    int row, col;
    
    srand((unsigned)time(NULL));
    for (row = 0; row < N; row++) {
        for (col = 0; col < N; col++) {
            A[row][col] = (float)rand() / 32768.0;
            B[row][col] = 0.0;
        }
    }
    
}


/* Kernel function */
__global__
void matrixNorm(float *nA, float *nB) {
    int row, col;
    float mu, sigma; // Mean and Standard Deviation
	
	int index = blockDim.x * blockId.x + threadIdx.x;
	int stride = blockDim.x * gridDim.x;
	
    printf("Computing Serially.\n");
    
    for (col=index; col < N; col+=stride) {
        mu = 0.0;
        for (row=0; row < N; row++)
            mu += nA[row*N + col];
        mu /= (float) N;
        sigma = 0.0;
        for (row=0; row < N; row++)
            sigma += powf(nA[row*N + col] - mu, 2.0);
        sigma /= (float) N;
        sigma = sqrt(sigma);
        for (row=0; row < N; row++) {
            if (sigma == 0.0)
                nB[row*N + col] = 0.0;
            else
                nB[row*N + col] = (nA[row*N + col] - mu) / sigma;
        }
    }
}



int main(int argc, char **argv) {
    /* Timing variables */
    struct timeval start, stop;  /* Elapsed times using gettimeofday() */
    struct timezone tzdummy;
    unsigned long long runtime;
    float *nA, *nB;
	
	cudaMalloc((void **) &nA, N*N*sizeof(float));
	cudaMalloc((void **) &nB, N*N*sizeof(float));
	
	cudaMemcpy(nA, A, N*N*sizeof(float), cudaMemcpyHostToDevice);
	cudaMemcpy(nB, B, N*N*sizeof(float), cudaMemcpyHostToDevice);
	
    /* Initialize A and B */
    initialize_inputs();
    
    /* Start Clock */
    printf("\n---------------------------------------------\n");
    printf("Matrix size N = %d", N);
    printf("\nStarting clock.\n\n");
    gettimeofday(&start, &tzdummy);
    
    
    /* Matrix Normalization */
    matrixNorm<<<1, 1>>>(nA, nB);
    
	cudaMemcpy(A, nA, N*N*sizeof(float), cudaMemcpyDeviceToHost);
	cudaMemcpy(B, nB, N*N*sizeof(float), cudaMemcpyDeviceToHost);
	
    /* Stop Clock */
    gettimeofday(&stop, &tzdummy);
    runtime = (unsigned long long)(stop.tv_sec - start.tv_sec) * 1000000 + (stop.tv_usec - start.tv_usec);
    
    
    /* Display timing results */
    printf("Runtime = %g ms.\n", (float)runtime/(float)1000);
    printf("\nStopped clock.");
    printf("\n---------------------------------------------\n");
    
    exit(0);
}