#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "character.h"
#include <sys/wait.h>

int main(){
    int f;
    f = fork();
    if(f==0){
        execl("./testIB1","testIB1",NULL);
    } else if(f > 0){
        wait(NULL);
        printf("Je suis le pere\n");
    } else {
        printf("erreur\n");
        return 1;
    }
    return 0;
}
