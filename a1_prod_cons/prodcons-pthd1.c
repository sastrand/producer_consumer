/*-----------------------------------------------------------------------------
 * pthreads implementation of the classic producer-consumer problem
 *---------------------------------------------------------------------------*/

#define _GNU_SOURCE
#include <pthread.h>
#include <stdio.h>
#include <unistd.h> 
#include <sched.h>
#include "queue.h"

pthread_mutex_t lock;
pthread_cond_t cond;
queue_t *buf;

void producer() {
  printf("Producer starting on core %2d\n", sched_getcpu());
  sleep(1);
  for (int i=1;i<=100;i++) {
    pthread_mutex_lock(&lock);
    add_item(buf, i);
    pthread_cond_signal(&cond);
    printf("Producer added value %3d (qsize = %2d). Signaled.\n", i, buf->size);
    pthread_mutex_unlock(&lock);
  }
}

void consumer() {
  int i = 0, i_count = 0;
  printf("Consumer starting on core %2d\n", sched_getcpu());
  while(i_count < 100) {
    pthread_mutex_lock(&lock);
    pthread_cond_wait(&cond, &lock);
    i = remove_item(buf);
    i_count++;
    printf("Value %3d consumed.\n", i);
    pthread_mutex_unlock(&lock);
  }
}

int main(int argc, char **argv) {
  pthread_t tid1;
  long tids[1] = {1};
  buf = create_queue(20);
  pthread_mutex_init(&lock, NULL);
  pthread_cond_init(&cond, NULL);
  pthread_create(&tid1, NULL, (void *)consumer, NULL);
  producer();
  pthread_join(tid1, NULL);
}

