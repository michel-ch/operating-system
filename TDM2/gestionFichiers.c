#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "gestionFichiers.h"

char * litLigne(int fd)
{
    int i;
    int nbr;
    char buf[TAILLEBUF];
    char * s;

    for(nbr = 0 ; nbr < TAILLEBUF ; nbr++){
        if( read(fd, buf+nbr,1) <= 0  ){
            return NULL;
        }
        if(buf[nbr]=='\n')break;
    } 

    s=(char*)malloc(nbr+1);
    if(s==NULL)return NULL;

    for(i=0;i<nbr;i++)
        s[i]=buf[i];

    s[i] = '\0';
    return s;
}