#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include "gestionFichiers.h"
#include <sys/wait.h>

void serveurA(int fd_source, int fd_canal){
    char *message;
    while((message = litLigne(fd_source)) != NULL){
        ecritLigne(message,fd_canal);
        free(message);
    }
    close(fd_canal);
}

void serveurB(int fd_destination, int fd_canal){
    char *message;
    while((message = litLigne(fd_canal)) != NULL){
        ecritLigne(message,fd_destination);
        free(message);
    }
    close(fd_destination);
}

int main(){
    int tube[2];
    pid_t pid;
    int fd_source;
    int fd_destination;

    if (pipe(tube) == -1) {
        perror("pipe");
        exit(1);
    }

    fd_source = open("Source.txt", O_RDONLY);
    if(fd_source < 0){
        perror("Error openning file fd_source");
        exit(1);
    }
    fd_destination = open("Destination.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if(fd_destination < 0){
        perror("Error openning file fd_destination");
        exit(1);
    }
    pid = fork();

    if(pid == -1){
        perror("fork");
        exit(1);
    }
    if(pid  == 0){
        /* FILS */
        close(tube[1]);
        serveurB(fd_destination, tube[0]);
        close(tube[0]);
        exit(0);
    } else {
        /* PERE */
        close(tube[0]);
        close(fd_destination);
        serveurA(fd_source, tube[1]);
        close(fd_source);
        wait(NULL);
    }

    return 0;
}