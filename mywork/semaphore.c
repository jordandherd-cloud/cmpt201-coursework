#define SIZE 10
#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

static char buf[SIZE] = {0};
static int in = 0, out = 0;
static sem_t filled_cnt;
static sem_t avail_cnt;
static pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;

static void *thread_func(void *arg) {
  for (;;) {
    sleep(1);
    sem_wait(&filled_cnt);
    pthread_mutex_lock(&mtx);
    // Consume
    printf("Consumed: %d\n", buf[out]);
    out = (out + 1) % SIZE;
    pthread_mutex_unlock(&mtx);
    sem_post(&avail_cnt);
  }
  return 0;
}

int main() {
  pthread_t t1;

  sem_init(&filled_cnt, 0, 0);
  sem_init(&avail_cnt, 0, SIZE);
  pthread_create(&t1, NULL, thread_func, NULL);
  // Producer Code
  for (int i = 0;; i++) {
    sem_wait(&avail_cnt);
    pthread_mutex_lock(&mtx);
    // Produce
    buf[in] = i;
    printf("Produced: %d in %d\n", buf[in], in);
    in = (in + 1) % SIZE;
    pthread_mutex_unlock(&mtx);
    sem_post(&filled_cnt);
  }
  pthread_join(t1, NULL);
}
