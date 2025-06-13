#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "character.h"

int main(){
    int f;
    pidAndppid("bonjour");
    f = fork();
    if(f==0){
        printf("fils\n");
    } else if(f > 0){
        printf("pere\n");
    } else {
        printf("erreur\n");
        return 1;
    }
    return 0;
}