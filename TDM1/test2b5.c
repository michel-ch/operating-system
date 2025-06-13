#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "gestionFichiers.h"

int main(){
    char* ligne;
    ligne = litLigne(0);
    if(ligne != NULL){
        printf("Ligne lue : %s\n",ligne);
        free(ligne);
    }
    else{
        perror("Error Outputing function result");
        exit(1);
    }
    return 0;
}

/* Ce code va lire l'entree du clavier jusqu'a rencontrer un "\n" 
( touche Entree ) et l'imprimer donc la valeur 0 en parametre 
de notre fonction de lecture d'une ligne*/
