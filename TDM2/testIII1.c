#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>

int main(){
    int f;
    f = fork();
    if(f==0){
        printf("affichage fils:\n");
        execl("./test2b1","test2b1",NULL);
    } else if(f > 0){
        printf("affichage pere: \n");
        execl("./test2b1","test2b1",NULL);
    } else {
        printf("erreur\n");
        return 1;
    }
    return 0;
}
