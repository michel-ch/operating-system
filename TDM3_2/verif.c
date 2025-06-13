#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include "gestionFichiers.h"
#include <sys/wait.h>
#include <signal.h>
#include <sys/types.h>

#define CODE "1234"

void handler(int sig){
    if(sig == SIGUSR1){
        printf("Trop tard : coffre-fort fermé\n");
        exit(1);
    }
}

int main(){
    pid_t pid;
    char *code;

    signal(SIGUSR1, handler);

    pid = fork();
    
    if(pid == -1){
        perror("fork");
        exit(1);
    }
    if(pid  == 0){
        /* FILS */
        sleep(10);
        kill(getppid(),SIGUSR1);
        exit(0);
    } else {
        /* PERE */
        code = litLigne(0);
        if(code != NULL){
            if(strcmp(code,CODE) == 0){
                printf("Bravo : coffre-fort ouvert\n");
            }
            else{
                printf("Code faux : coffre-fort fermé\n");
            }
            free(code);
        }
        kill(pid, SIGKILL);
        wait(NULL);
    }

    return 0;
}