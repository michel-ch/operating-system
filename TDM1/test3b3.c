#include <unistd.h>
#include <stdlib.h>
#include "gestionFichiers.h"

int main(){
    char* ligne;
    while((ligne = litLigne(0))){
        ecrisLigne(1, ligne);
        free(ligne);
    }
    return 0;
}
/* Etant sur le terminal MINGW64, pour terminer le programme, nous devons taper sur la touche Entree 
cliquer sur les touches Ctrl+Z simultanement, puis sur la touche Entree*/