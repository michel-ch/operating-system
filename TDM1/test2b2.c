#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "gestionFichiers.h"

int main(int argc, char ** argv){
    char* ligne;
    int a;
    if(argc != 2){
        printf("Error, input should be 2 arguments");
        exit(1);
    }
    printf("Nom du programme : %s.\n",argv[0]);
    a = open(argv[1], O_RDONLY);
    if(a < 0){
        /* Erreur de sortie */
        perror("Error openning file");
        exit(1);
    }
    ligne = litLigne(a);
    if(ligne != NULL){
        printf("Ligne :\n %s\n",ligne);
        free(ligne);
    }
    else{
        perror("Error Outputing function result");
        close(a);
        exit(1);
    }
    close(a);
    return 0;
}