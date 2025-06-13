#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include "gestionFichiers.h"

void

int main(){
    char* result;
    int a = open("fichierTest.txt", O_RDONLY);
    if(a < 0){
        /* Erreur de sortie */
        perror("Error openning file");
        exit(1);
    }
    result = litDixCaracteres(a);
    if(result != NULL){
        printf("10 premiers caracteres :\n");
        printf("%s",result);
    }
    close(a);
    return 0;
}