//----------------------------------------------------------------------------- 
// Program code for CS 415/515 Parallel Programming, Portland State University.
//----------------------------------------------------------------------------- 

#define _GNU_SOURCE
#include <sched.h>
#include <unistd.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

/* problem domain size */
int N = 1000;
/* number of threads */
int P = 10;

int sum = 0; 
pthread_mutex_t sumLock;   

int compute(int i) { return i*i; }

void worker(long tid) {
  printf("Worker %4ld started on CPU %2d\n", tid, sched_getcpu());
  int low = (N/P) * tid; 	/* a simplistic partition scheme */
  int high = low + (N/P);
  int psum = 0;
  for (int i=low; i<high; i++)
    psum += compute(i);
  pthread_mutex_lock(&sumLock);
  sum += psum;
  pthread_mutex_unlock(&sumLock);
  printf("Worker %4ld ended\n", tid);
} 

int main(int argc, char **argv) {
  if (argc<=2) {
    printf("Two arguments are required, N (domain size) and \
     P (quant threads)\n");
    exit(1);
  } 
  N = atoi(argv[1]);
  P = atoi(argv[2]);
  if ( N < 1 || P < 1) {
    printf("N and P must be greater than zero.");
    N = 100;
    P = 1;
  }
  printf("Continuing with domain size N: %d and quantity threads P: %d\n", N, P);

  pthread_t thread[P];
  pthread_mutex_init(&sumLock, NULL);   /* initialize mutex */
  int nprocs = sysconf(_SC_NPROCESSORS_ONLN);
  cpu_set_t cpuset;
  int cid = 0;
  /* create threads */
  for (long k=0; k<P; k++){
    CPU_ZERO(&cpuset);
    CPU_SET(cid++ % nprocs, &cpuset);
    pthread_create(&thread[k], NULL, (void*)worker, (void*)k);
    pthread_setaffinity_np(thread[k], sizeof(cpu_set_t), &cpuset);
  }
  for (long k=0; k<P; k++)    /* join threads */
    pthread_join(thread[k], NULL);
  printf("The result sum is %d (should be 332833500)\n", sum);
}  

