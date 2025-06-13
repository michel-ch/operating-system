#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include "gestionFichiers.h"

int main(){
    int f, a;
    char* ligne;
    a = open("fichierTest.txt", O_RDONLY);
    if(a < 0){
        /* Erreur de sortie */
        perror("Error openning file");
        exit(1);
    }
    f = fork();

    if(f==0){
        printf("affichage fils:\n");
        ligne = litLigne(a);
        printf("Ligne :%s\n",ligne);
    } else if(f > 0){
        printf("affichage pere: \n");
        ligne = litLigne(a);
        printf("Ligne :%s\n",ligne);
    } else {
        printf("erreur\n");
        return 1;
    }
    close(a);
    return 0;
}
