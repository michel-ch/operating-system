#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "gestionFichiers.h"

int main(int argc, char ** argv){
    char* ligne;
    int source;
    if(argc != 3){
        printf("Error, input should be 3 arguments");
        exit(1);
    }
    printf("Nom du programme : %s.\n",argv[0]);
    source = open(argv[1], O_RDONLY);
    if(source < 0){
        /* Erreur de sortie source */
        perror("Erreur ouverture source");
        exit(1);
    }
    while((ligne = litLigne(source)) != NULL){
        ecrisLigne(1, ligne);
        free(ligne);
    }
    close(source);
    return 0;
}

/* En passant la valeur 1 en paramètre de votre fonction d'écriture,
 la fonction ecrisLigne va imprimer le texte du document d'origine 
 en terminal et ne pas toucher au fichier de destination.*/