#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "gestionFichiers.h"

int main(int argc, char ** argv){
    char* ligne;
    int a;
    int counter;
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
    counter = 0;
    while((ligne = litLigne(a)) != NULL){
        if(ligne != NULL){
            counter++;
            free(ligne);
        }
        else{
            perror("Error Outputing function result");
            close(a);
            exit(1);
        }
    }
    close(a);
    if(counter>0){
        printf("Nombre de lignes du fichier passe en argument : %d",counter);
    }
    return 0;
}