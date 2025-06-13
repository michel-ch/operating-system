#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include "gestionFichiers.h"

int main(){
    char* ligne;
    int a = open("fichierTest.txt", O_RDONLY);
    if(a < 0){
        /* Erreur de sortie */
        perror("Error openning file");
        exit(1);
    }
    ligne = litLigne(a);
    if(ligne != NULL){
        printf("Ligne :\n");
        printf("%s",ligne);
    }
    else{
        perror("Error Outputing function result");
        exit(1);
    }
    close(a);
    return 0;
}