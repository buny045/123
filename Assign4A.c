#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <stdlib.h>
void *producer(void *thread);
void *consumer(void *thread);
int count = 0, in = 0, out = 0, a[5];
sem_t full;
sem_t empty;
pthread_mutex_t mutex;
int main() {
int i, p, c;
pthread_t pid[10], cid[10];
pthread_mutex_init(&mutex, NULL);
sem_init (&full, 0, 0);
sem_init (&empty, 0, 5);
printf("\nEnter number of producers: ");
scanf("%d", &p);
printf("\nEnter number of consumers: ");
scanf("%d", &c);
int producer_indices[p];
int consumer_indices[c];
for (i = 0; i < p; i++) {
producer_indices[i] = i;
pthread_create(&pid[i], NULL, producer, &producer_indices[i]);
}
for (i = 0; i < c; i++) {
consumer_indices[i] = i;
pthread_create(&cid[i], NULL, consumer, &consumer_indices[i]);
}
for (i = 0; i < p; i++) {
pthread_join(pid[i], NULL);
}
for (i = 0; i < c; i++) {
pthread_join(cid[i], NULL);
}
sem_destroy(&full);
sem_destroy(&empty);
pthread_mutex_destroy(&mutex);
return 0;
}
void *producer(void *thread) {
int t = *(int *)thread;
while (1) {
sem_wait(&empty);
pthread_mutex_lock(&mutex);
if (count >= 5) {
printf("\nBuffer is full");
} else {
a[in] = rand() % 100;
printf("\nProducer %d produced: %d", t, a[in]);
in = (in + 1) % 5;count++;
}
pthread_mutex_unlock(&mutex);
sem_post(&full);
sleep(1);
}
pthread_exit(0);
}
void *consumer(void *thread) {
int t = *(int *)thread;
while (1) {
sem_wait(&full);
pthread_mutex_lock(&mutex);
if (count <= 0) {
printf("\nBuffer is empty");
} else {
printf("\nConsumer %d consumed: %d", t, a[out]);
out = (out + 1) % 5;
count--;
}
pthread_mutex_unlock(&mutex);
sem_post(&empty);
sleep(1);
}
pthread_exit(0);
}
