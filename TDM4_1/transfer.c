#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <semaphore.h>
#include "gestionFichiers.h"

sem_t empty;
sem_t full;
sem_t mutex;
char buffer[TAILLEBUF];
int buffer_used = 0;
int transfer_complete = 0;

void *source(void* arg){
    (void)arg;
    int fd_source;
    char *message;
    fd_source = open("Source.txt", O_RDONLY);
    if(fd_source < 0){
        perror("Error openning file fd_source");
        exit(1);
    }
    while((message = litLigne(fd_source)) != NULL){
        sem_wait(&empty);
        sem_wait(&mutex);

        strcpy(buffer, message);
        buffer_used = 1;

        sem_post(&mutex);
        sem_post(&full);
        free(message);
    }
    sem_wait(&mutex);
    transfer_complete = 1;
    sem_post(&mutex);
    sem_post(&full);
    
    close(fd_source);
    return NULL;
}

void *destination(void* arg){
    (void)arg;
    int fd_destination;
    fd_destination = open("Destination.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if(fd_destination < 0){
        perror("Error openning file fd_destination");
        exit(1);
    }

    while(1){
        sem_wait(&full);
        sem_wait(&mutex);

        if(transfer_complete && !buffer_used) {
            sem_post(&mutex);
            break;
        }

        if(buffer_used){
            ecritLigne(buffer,fd_destination);
            buffer_used = 0;
        }
        sem_post(&mutex);
        sem_post(&empty);
    }
    close(fd_destination);
    return NULL;
}

int main(){
    sem_init(&empty, 0, 1);
    sem_init(&full, 0, 0);
    sem_init(&mutex, 0, 1);

    pthread_t thread1, thread2;
    
    pthread_create(&thread1, NULL, source, NULL);
    pthread_create(&thread2, NULL, destination, NULL);
    
    pthread_join(thread1,NULL);
    pthread_join(thread2,NULL);
    
    sem_destroy(&empty);
    sem_destroy(&full);
    sem_destroy(&mutex);

    return 0;
}
