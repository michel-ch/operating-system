#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <semaphore.h>
#include "gestionFichiers.h"

#define TAILLEBUF 10
#define MAX_LINE 1024

sem_t empty;
sem_t full;
char buffer[TAILLEBUF];
int write_pos = 0;
int read_pos = 0;

void *source(void* arg) {
    int fd_source;
    char *line;
    int i;
    
    (void)arg;
    fd_source = open("Source.txt", O_RDONLY);
    if(fd_source < 0) {
        perror("Error opening source file");
        exit(1);
    }
    
    while((line = litLigne(fd_source)) != NULL) {
        for(i = 0; line[i] != '\0'; i++) {
            sem_wait(&empty);
            buffer[write_pos] = line[i];
            write_pos = (write_pos + 1) % TAILLEBUF;
            sem_post(&full);
        }
        sem_wait(&empty);
        buffer[write_pos] = '\n';
        write_pos = (write_pos + 1) % TAILLEBUF;
        sem_post(&full);
        
        free(line);
    }
    
    sem_wait(&empty);
    buffer[write_pos] = EOF;
    write_pos = (write_pos + 1) % TAILLEBUF;
    sem_post(&full);
    
    close(fd_source);
    return NULL;
}

void *destination(void* arg) {
    int fd_destination;
    char local_buffer[MAX_LINE];
    int local_pos = 0;
    char c;
    
    (void)arg;
    fd_destination = open("Destination.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if(fd_destination < 0) {
        perror("Error opening destination file");
        exit(1);
    }
    
    while(1) {
        sem_wait(&full);
        c = buffer[read_pos];
        read_pos = (read_pos + 1) % TAILLEBUF;
        sem_post(&empty);
        
        if(c == EOF) {
            break;
        }
        
        if(c == '\n') {
            local_buffer[local_pos] = '\0';
            ecritLigne(local_buffer, fd_destination);
            local_pos = 0;
        } else {
            if(local_pos < MAX_LINE - 1) {
                local_buffer[local_pos++] = c;
            }
        }
    }
    
    if(local_pos > 0) {
        local_buffer[local_pos] = '\0';
        ecritLigne(local_buffer, fd_destination);
    }
    
    close(fd_destination);
    return NULL;
}

int main(void) {
    pthread_t thread1, thread2;
    
    if (sem_init(&empty, 0, TAILLEBUF) != 0 ||
        sem_init(&full, 0, 0) != 0) {
        perror("Semaphore initialization failed");
        return 1;
    }
    
    if (pthread_create(&thread1, NULL, source, NULL) != 0 ||
        pthread_create(&thread2, NULL, destination, NULL) != 0) {
        perror("Thread creation failed");
        return 1;
    }
    
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    
    sem_destroy(&empty);
    sem_destroy(&full);
    
    return 0;
}