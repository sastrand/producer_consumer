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
  printf("Worker %ld started on CPU-%d\n", tid, sched_getcpu());
  int low = (N/P) * tid; 	/* a simplistic partition scheme */
  int high = low + (N/P);
  int psum = 0;
  for (int i=low; i<high; i++)
    psum += compute(i);
  pthread_mutex_lock(&sumLock);
  sum += psum;
  pthread_mutex_unlock(&sumLock);
  printf("Worker %ld ended\n", tid);
} 

int main(int argc, char **argv) {
  if (argc<=2) {
    printf("Two arguments are required, N (domain size) and P (quant threads)\n");
    exit(1);
  }
  N = atoi(argv[1]);
  P = atoi(argv[2]);
  printf("You entered domain size N: %d and quantity threads P: %d\n", N, P);

  pthread_t thread[P];
  pthread_mutex_init(&sumLock, NULL);   /* initialize mutex */
  for (long k=0; k<P; k++)    /* create threads */
    pthread_create(&thread[k], NULL, (void*)worker, (void*)k);
  for (long k=0; k<P; k++)    /* join threads */
    pthread_join(thread[k], NULL);
  printf("The result sum is %d (should be 332833500)\n", sum);
}  

