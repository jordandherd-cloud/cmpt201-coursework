
#define NUMBER 5
#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

static pthread_mutex_t mtx[NUMBER];

static void *thread_func(void *arg) {
  int left = (int)arg;
  int right = ((int)arg + 1) % NUMBER;
  for (;;) {
    printf("Thread %d: thinking\n", (int)arg);
    sleep(5);
    pthread_mutex_lock(&mtx[left]);
    if (pthread_mutex_trylock(&mtx[right]) != 0) {
      pthread_mutex_unlock(&mtx[left]);
      continue;
    }
    printf("Thread %d: eating\n", (int)arg);
    pthread_mutex_unlock(&mtx[left]);
    pthread_mutex_unlock(&mtx[right]);
  }
  return 0;
}

int main() {
  pthread_t t[NUMBER];
  int ids[NUMBER];
  for (int i = 0; i < NUMBER; i++) {
    pthread_mutex_init(&mtx[i], NULL);
  }
  for (int i = 0; i < NUMBER; ++i) {

    ids[i] = i;

    printf("i %d\n", i);
    pthread_create(&t[i], NULL, thread_func, &ids[i]);
  }
  for (int i = 0; i < NUMBER; ++i) {
    pthread_join(t[i], NULL);
  }
}
