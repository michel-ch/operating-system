#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "character.h"

void pid(char *c){
    printf("pid: %d\nchaine de caractere : %s\n",getpid(),c);
}
void ppid(char *c){
    printf("ppid: %d\nchaine de caractere : %s\n",getppid(),c);
}
void pidAndppid(char *c){
    printf("pid: %d\nppid: %d\nchaine de caractere : %s\n",getpid(),getppid(),c);
}