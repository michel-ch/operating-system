#ifndef GESTION_FICHIER_H
#define GESTION_FICHIER_H

#define TAILLEBUF 8191

char* litLigne(int descripteur);
void ecritLigne(char* chaine,int descripteur);
#endif