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
        printf("fils\n");
        pidAndppid("bonjour");
    } else if(f > 0){
        wait(NULL);
        printf("pere\n");
        pidAndppid("bonjour");
    } else {
        printf("erreur\n");
        return 1;
    }
    return 0;
}
/* Nous avons donc ajoute wait(NULL) pour attendre la fin de l'execution du 
fils afin d'afficher le pere*/