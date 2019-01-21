/*-----------------------------------------------------------------------------
 * pthreads implementation of the classic producer-consumer problem
 *---------------------------------------------------------------------------*/

#define _GNU_SOURCE
#define CAP 20
#include <pthread.h>
#include <stdio.h>
#include <unistd.h> 
#include <sched.h>
#include <stdlib.h>
#include "queue.h"

pthread_mutex_t lock;
pthread_cond_t cond;
queue_t *buf;
int consumer_counts[1000] = {0};
int numCons = 0;

void producer() {
  printf("Producer starting on core %2d\n", sched_getcpu());
  sleep(1);
  for (int i=1;i<=100;i++) {
    pthread_mutex_lock(&lock);
    if (buf->size>=CAP) pthread_cond_wait(&cond, &lock);
    add_item(buf, i);
    pthread_cond_signal(&cond);
    printf("Producer added value %3d (qsize = %2d)\n", i, buf->size);
    pthread_mutex_unlock(&lock);
  }
  printf("Producer done producing. Adding flag values to buffer.\n");
  for (int i=0;i<numCons;i++) {
    pthread_mutex_lock(&lock);
    if (buf->size>=CAP) pthread_cond_wait(&cond, &lock);
    add_item(buf, -1);
    pthread_cond_signal(&cond);
    pthread_mutex_unlock(&lock);
  }
}

void consumer(long tid) {
  int item = 0;
  printf("Consumer[%3ld] starting on core %2d\n", tid, sched_getcpu());
  while(1) {
    pthread_mutex_lock(&lock);
    while (buf->size<1) {
      pthread_cond_wait(&cond, &lock);
    } 
    item = remove_item(buf);
    if (item == -1) {
      printf("---< Consumer[%3ld] ending >---\n", tid);
      pthread_mutex_unlock(&lock);
      return;
    }
    consumer_counts[tid]++;
    pthread_cond_signal(&cond);
    printf("Consumer[%3ld] removed value %3d (qsize = %d)\n", 
           tid, item, buf->size);
    pthread_mutex_unlock(&lock);
  }
}

int get_numCons(int argc, char **argv) {
  const char default_numCons[] = "Using default value of 1 for the number of "
                          "consumers. Input must be between 1 and 999.\n";
  if (argc<=1) {
    printf(default_numCons);
    return 1;
  } else {
    int ret = atoi(argv[1]);
    if (ret < 1 || ret > 999) {
      printf(default_numCons);
      return 1;
    } else {
      return ret;
    }
  }
}

int main(int argc, char **argv) {
  numCons = get_numCons(argc, argv);
  pthread_t threads[numCons];
  long tids[numCons];
  buf = create_queue(CAP);
  pthread_mutex_init(&lock, NULL);
  pthread_cond_init(&cond, NULL);
  for (long i=0;i<numCons;i++) {
    pthread_create(&threads[i], NULL, (void *)consumer, (void*)i);
  }
  producer();
  for (int i=0;i<numCons;i++) {
    pthread_join(threads[i], NULL);
    printf(" --  Consumer[%3d] joined  --\n", i);
//    pthread_mutex_lock(&lock);
//    pthread_cond_signal(&cond);
//    pthread_mutex_unlock(&lock);
  }
  int sum;
  for (int i=0;i<numCons;i++) {
    if (i<numCons-1) {
      printf("C[%d]:%2d, ", i, consumer_counts[i]);
    } else {
      printf("C[%d]:%2d\n", i, consumer_counts[i]);
    }
    sum = sum + consumer_counts[i];
  }
  printf("Total items across threads: %d\n\n", sum);
}

