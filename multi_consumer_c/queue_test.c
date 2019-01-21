/*-----------------------------------------------------------------------------
 * pthreads implementation of the classic producer-consumer problem
 *---------------------------------------------------------------------------*/

#include <stdio.h>
#include "queue.h"

queue_t *buf;

void producer() {
  for (int i=1;i<=100;i++) {
    if (i<=25) {
      add_item(buf, i);
      printf("Producer added value %3d (qsize = %2d)\n", i, buf->size);
    }
  }
}

int main(int argc, char **argv) {
  buf = create_queue(20);
  producer();
}
