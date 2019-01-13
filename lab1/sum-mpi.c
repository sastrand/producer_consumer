//----------------------------------------------------------------------------- 
// Program code for CS 415/515 Parallel Programming, Portland State University.
//----------------------------------------------------------------------------- 

// The sum program (MPI version).
//
//
#include <stdio.h>
#include <mpi.h>

#define N 1000 	/* problem domain size */

int sum = 0;

int compute(int i) {
  return i*i;
}

int main(int argc, char **argv) {  
  int rank, size, dest; 
  int i, low, high, psum, sum;

  MPI_Init(&argc, &argv);  
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);  
  MPI_Comm_size(MPI_COMM_WORLD, &size);  
  
  low = (N/size) * rank;    /* a simplistic partition scheme */ 
  high = low + (N/size);	
  psum = 0;
  for (i = low; i < high; i++)
    psum += compute(i);

  dest = 0;
  MPI_Reduce(&psum, &sum, 1, MPI_INT, MPI_SUM, dest, MPI_COMM_WORLD);
  if (rank == dest)
    printf("The sum of 1,2,...,1000 is %d (should be 332833500)\n", sum);

  MPI_Finalize();
  return 0;
}  
