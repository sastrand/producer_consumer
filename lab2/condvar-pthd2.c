//----------------------------------------------------------------------------- 
// Program code for CS 415/515 Parallel Programming, Portland State University.
//----------------------------------------------------------------------------- 

// A Pthread condition variable demo program.
//
//
#include <pthread.h>
#include <stdio.h>
#include <unistd.h> 

pthread_mutex_t lock;
pthread_cond_t cond;

void sender() {
  printf("Sender starts ...\n");
  sleep(1);
  pthread_mutex_lock(&lock);
  pthread_cond_signal(&cond);
  printf("Signal sent from sender!\n");
  pthread_mutex_unlock(&lock);
}

void receiver(void* id) {
  printf("Receiver %ld starts ...\n", (long)id);
  pthread_mutex_lock(&lock);
  pthread_cond_wait(&cond, &lock);
  printf("Signal received by %ld!\n", (long)id);
  pthread_cond_signal(&cond);
  printf("Signal sent from %ld\n", (long)id);
  pthread_mutex_unlock(&lock);
}

int main(int argc, char **argv) {
  pthread_t tid1, tid2;
  long tids[2] = {1,2};

  pthread_mutex_init(&lock, NULL);
  pthread_cond_init(&cond, NULL);
  pthread_create(&tid1, NULL, (void *)sender, NULL);
  pthread_create(&tid2, NULL, (void *)receiver, (void*)tids[0]);
  pthread_create(&tid2, NULL, (void *)receiver, (void*)tids[1]);
  pthread_join(tid1, NULL);
  pthread_join(tid2, NULL);
}
