#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

sem_t sem1;
sem_t sem2;
sem_t sem3;

void* P1(void* arg) {
    int j;
    (void)arg;
    
    for(j = 0; j < 10; j++) {
        sem_wait(&sem1);
        printf("Affichage %d du thread 1\n", j+1);
        sem_post(&sem2);
    }
    return NULL;
}

void* P2(void* arg) {
    int j;
    (void)arg;
    
    for(j = 0; j < 10; j++) {
        sem_wait(&sem2);
        printf("Affichage %d du thread 2\n", j+1);
        sem_post(&sem3);
    }
    return NULL;
}

void* P3(void* arg) {
    int j;
    (void)arg;
    
    for(j = 0; j < 10; j++) {
        sem_wait(&sem3);
        printf("Affichage %d du thread 3\n", j+1);
        sem_post(&sem1);
    }
    return NULL;
}

int main(void) {
    pthread_t thread1, thread2, thread3;
    
    sem_init(&sem1, 0, 1);
    sem_init(&sem2, 0, 0);
    sem_init(&sem3, 0, 0);

    pthread_create(&thread1, NULL, P1, NULL);
    pthread_create(&thread2, NULL, P2, NULL);
    pthread_create(&thread3, NULL, P3, NULL);
    
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    pthread_join(thread3, NULL);
    
    sem_destroy(&sem1);
    sem_destroy(&sem2);
    sem_destroy(&sem3);
    
    return 0;
}