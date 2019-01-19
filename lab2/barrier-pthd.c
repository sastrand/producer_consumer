//----------------------------------------------------------------------------- 
// Program code for CS 415/515 Parallel Programming, Portland State University.
//----------------------------------------------------------------------------- 

// A Pthread barrier demo program.
//
//
#include <stdio.h>
#include <pthread.h>

pthread_barrier_t barr;

int a[3] = {5,5,5};

void worker(long k) {
  a[k] = k;
  int i = a[(k+1)%3];
  a[k] = i;
  printf("\tWorker %ld working; i = %d.\n", k, i);
  printf("\tWorker %ld completed.\n", k);
  pthread_barrier_wait(&barr);
}

int main(int argc, char **argv) {
  printf("starting out.\n");
  pthread_t thread[3];
  pthread_barrier_init(&barr, NULL, 4);
  for (long k=0; k<3; k++)    /* create threads */
    pthread_create(&thread[k], NULL, (void*)worker, (void*)k);
  printf("all the threads up and going.\n");
  pthread_barrier_wait(&barr);
  //for (long k=0; k<3; k++)    /* join threads */
  //  pthread_join(thread[k], NULL);
  printf("end of main thread.\n");
  printf("a = [%d,%d,%d]\n", a[0], a[1], a[2]);
}  
