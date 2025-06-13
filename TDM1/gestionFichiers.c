#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include "gestionFichiers.h"

char* litDixCaracteres(int descripteur){
    char buffer[TAILLEBUF];
    char* result;
    int i;
    ssize_t characters;
    if(descripteur < 0){
        return NULL;
    }
    /* Recupere les caracteres dans le buffer */
    characters = read(descripteur,buffer,10);
    if(characters <= 0){
        return NULL;
    }
    result = (char*)malloc((characters+1)*sizeof(char));
    for(i=0; i<characters; i++){
        result[i] = buffer[i];
    }
    result[characters] = '\0';
    return result;
}

char* litLigne(int descripteur){
    char * ligne;
    char buffer[TAILLEBUF];
    int i;
    int counter = 0;
    ssize_t characters;
    if(descripteur <0){
        return NULL;
    }
    while(counter < TAILLEBUF-1){
        characters = read(descripteur, &buffer[counter], 1);
        if(characters <= 0){
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
        return NULL;
    }
    for(i=0; i<counter; i++){
        ligne[i] = buffer[i];
    }
    ligne[counter] = '\0';
    
    return ligne;
}

void ecrisLigne(int descripteur, char* chaine){
    if(descripteur >= 0){
        write(descripteur, chaine, strlen(chaine));
        write(descripteur,"\n",1);
    }
}
