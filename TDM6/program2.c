#include <stdio.h>
#include <stdlib.h>

int somme2(int **tableau, int n, int m)
{
   int i,j, somme;
   somme = 0;
   for (j=0; j < m; j++) {
      for (i=0; i < n; i++) {
         somme += tableau[i][j];
      }
   }
   return somme;
}

int main(){
   int n = 2048, m = 2048;
   int **tab;

   tab = (int**)malloc(sizeof(int*)*n);
   if (tab == NULL) {
      fprintf(stderr, "Erreur d'allocation du tableau de pointeurs\n");
      return 1;
   }
   for(int i = 0; i < n; i++) {
      tab[i] = NULL;
   }
   for(int i=0; i<n; i++){
      tab[i] = (int*)malloc(sizeof(int)*m);
      if (tab[i] == NULL) {
         for(int j = 0; j < i; j++) {
               free(tab[j]);
         }
         free(tab);
         fprintf(stderr, "Erreur d'allocation de la ligne %d\n", i);
         return 1;
      }
   }
   for(int i=0; i<n; i++){
      for(int j=0; j<m; j++){
         tab[i][j] = 1;
      }
   }
   int total = somme2(tab, n, m);
   for(int i = 0; i < n; i++) {
      free(tab[i]);
   }
   free(tab);

   return 0;
}
