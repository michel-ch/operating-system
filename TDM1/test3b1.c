#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "gestionFichiers.h"

int main(int argc, char ** argv){
    char* ligne;
    int source, destination;
    if(argc != 3){
        printf("Error, input should be 3 arguments");
        exit(1);
    }
    printf("Nom du programme : %s.\n",argv[0]);
    source = open(argv[1], O_RDONLY);
    destination = open(argv[2], O_WRONLY);
    if(source < 0){
        /* Erreur de sortie source */
        perror("Erreur ouverture source");
        exit(1);
    }
    if(destination < 0){
        /* Erreur de sortie destination */
        perror("Erreur ouverture destination");
        exit(1);
    }
    while((ligne = litLigne(source)) != NULL){
        ecrisLigne(destination, ligne);
        free(ligne);
    }
    close(source);
    close(destination);
    return 0;
}