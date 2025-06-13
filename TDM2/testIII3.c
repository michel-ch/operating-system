#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include "gestionFichiers.h"

int main(int argc, char ** argv){
    int f, a;
    char* ligne, *ligne2;
    if(argc != 2){ 
        printf("Error, input should be 2 arguments");
        exit(1);
    }
    a = open(argv[1], O_RDONLY);
    if(a < 0){
        /* Erreur de sortie */
        perror("Error openning file");
        exit(1);
    }
    f = fork();

    if(f==0){
        lseek(a, 0, SEEK_SET);
        printf("affichage fils:\n");
        ligne = litLigne(a);
        printf("Ligne : %s\n",ligne);
        free(ligne);
    } else if(f > 0){
        wait(NULL);
        lseek(a, 0, SEEK_SET);
        printf("affichage pere:\n");
        ligne2 = litLigne(a);
        free(ligne2);
        ligne2 = litLigne(a);
        printf("Ligne : %s\n",ligne2);
        free(ligne2);
    } else {
        printf("erreur\n");
        return 1;
    }
    close(a);
    return 0;
}

/* La position de lecture dans un fichier est-elle toujours partagée, 
toujours commune entre un père et son fils ? 
Discutez entre vous des différents cas possibles ? 
Est-ce cohérent avec ce que vous avez vu en cours ? 

La position de lecture dans un fichier entre un père et son fils dépend du moment 
où le fichier est ouvert par rapport au fork().

*/