#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "gestionFichiers.h"

char* litLigne(int descripteur){
    char * ligne;
    char buffer[TAILLEBUF];
    int i;
    int counter = 0;
    ssize_t characters;

    if(descripteur < 0){
        perror("Invalid file descriptor in litLigne");
        return NULL;
    }

    while(counter < TAILLEBUF-1){
        characters = read(descripteur, &buffer[counter], 1);
        if(characters < 0){
            perror("Read error in litLigne");
            return NULL;
        }
        if(characters == 0){
            if(counter == 0){
                return NULL;
            }
            break;
        }
        if(buffer[counter]=='\n'){
            break;
        }
        counter++;
    }

    ligne = (char*)malloc((counter+1)*sizeof(char));
    if(ligne == NULL){
        perror("Memory allocation error in litLigne");
        return NULL;
    }

    for(i=0; i<counter; i++){
        ligne[i] = buffer[i];
    }
    ligne[counter] = '\0';
    
    return ligne;
}

void ecritLigne(char* chaine, int descripteur){
    ssize_t written;
    size_t len;

    if(descripteur < 0){
        perror("Invalid file descriptor in ecritLigne");
    }

    if(chaine == NULL){
        perror("Null string in ecritLigne");
    }

    len = strlen(chaine);
    written = write(descripteur, chaine, len);
    if(written < 0){
        perror("Write error in ecritLigne");
    }
    if((size_t)written != len){
        perror("Partial write in ecritLigne");
    }

    written = write(descripteur, "\n", 1);
    if(written < 0){
        perror("Write error (newline) in ecritLigne");
    }
    if(written != 1){
        perror("Partial write (newline) in ecritLigne");
    }
}