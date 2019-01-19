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
  //pthread_mutex_lock(&lock);
  sleep(1);
//  pthread_cond_signal(&cond);
  //pthread_mutex_unlock(&lock);
  // ... add code ...

  printf("Signal sent!\n");
}

void receiver() {
  printf("Receiver starts ...\n");
  //pthread_mutex_lock(&lock);
 // pthread_cond_wait(&cond, &lock);
  //pthread_mutex_unlock(&lock);
  // ... add code ...

  printf("Signal received!\n");
}

int main(int argc, char **argv) {
  pthread_t tid1, tid2;

  pthread_mutex_init(&lock, NULL);
  pthread_cond_init(&cond, NULL);
  pthread_create(&tid1, NULL, (void *)sender, NULL);
  pthread_create(&tid2, NULL, (void *)receiver, NULL);
  pthread_join(tid1, NULL);
  pthread_join(tid2, NULL);
}
