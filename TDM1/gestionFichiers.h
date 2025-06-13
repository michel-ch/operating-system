#ifndef GESTION_FICHIER_H
#define GESTION_FICHIER_H

#define TAILLEBUF 1000

char* litDixCaracteres(int descripteur);
char* litLigne(int descripteur);
void ecrisLigne(int descripteur, char* chaine);
#endif