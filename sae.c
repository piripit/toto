#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define FALSE 0
#define TRUE 1
typedef char string[50];
typedef int bool;
struct all{
	char action[200];
	string preconds[10];
	string add[10];
	string delete[10];
};

int parseline(char source[], string cible[]){
    int i = 0, n = 0; // i: l'indice de source[], n: l'indice de cible[]
    int j = i;  // marquer le debut de la premiere chaine avec j
    while(source[i]!='\n'){
      if(source[i]==','){
      memcpy(cible[n], &source[j], i-j); // extraire les i-j  
caracteres a partir de j
      cible[n][i-j]='\0';
      n++;
      j=i+1;   // marquer le debut de la chaine suivante avec j
      }
      i++;

    }
    return n;
}

int appliquable(string prec[],string deb[]){
      int appli = 1;
      int test = 0;
      int i = 0, j = 0;

      while(appli == 1 && prec[j][0] != '\0'){
          while(appli == 1 && deb[i][0] != '\0'){

              if(strcmp(prec[j], deb[i]) != 0 && test == 0){

              }
              else{
                  test = 1;

              }
              i = i + 1;
          }
          j = j + 1;
          if(test == 0){
          	appli = 0;
          }
          i = 0;

      }
      return appli;
}

void applique(string add[], string delete[], string deb[]) {
      int j = 0, u = 0;
      while (delete[j][0] != '\0' || deb[u][0]!='\0') {
          if (strcmp(delete[j], deb[u]) == 0) {
              while (deb[u][0] != '\0') {
                  memcpy(deb[u], deb[u + 1], 50);
                  u = u + 1;
              }
              u = 0;
              j = j + 1;
          }
          else{
              u = u + 1;
          }
      }
      u = 0;
      j = 0;
      while (add[j][0] != '\0') {
          if (deb[u][0] == '\0') {
              memcpy(deb[u+j], add[j], 100);
              j = j + 1;
          }
          u = u + 1;
      }
}

int main(){
	FILE* start = fopen("monkey.txt","r");
	int i = 0, n = 0;
	bool app;
	char l1[100], l2[100];
	string deb[15], fin[2];
	char stopl[100];
	struct all act[50];
	fgets(l1, 100, start);
	memcpy(l1, &l1[6], 100);
	n = parseline(l1, deb);
	printf("%s  %d\n", deb[4], n);
	fgets(l2, 100, start);
	memcpy(l2, &l2[7], 15);
	parseline(l2, fin);
	printf("%s", l2);


	while(fgets(stopl, 100, start) != NULL){
		if(strstr(stopl, "action")){
			memcpy(stopl, &stopl[7], 93);
				strcpy(act[i].action, stopl);
			}
		while(fgets(stopl, 100, start) != NULL && strstr(stopl, "****") == NULL){

			if(strstr(stopl, "action")){
				memcpy(stopl, &stopl[7], 93);
				strcpy(act[i].action, stopl);
			}
			if(strstr(stopl, "preconds")){
				memcpy(stopl, &stopl[9], 90);
				parseline(stopl, act[i].preconds);
			}
			if(strstr(stopl, "add")){
				memcpy(stopl, &stopl[4], 96);
				parseline(stopl, act[i].add);
			}
			if(strstr(stopl, "delete")){
				memcpy(stopl, &stopl[7], 93);
				parseline(stopl, act[i].delete);
			}
		}
		i = i + 1;
	}
	printf("\n%s", act[0].preconds[0]);
	printf("\n%s", act[5].delete[0]);
	printf("\n%s  %s", act[1].delete[1], deb[0]);
      printf("\n");
	app = appliquable(act[1].preconds, deb);
	if (app == 0){
	    printf("\nfaux\n");
	}
	else{
	    printf("\nvrai\n");
	}

	/*while (appliquable(fin, deb) == FALSE){
	    while (act[i].preconds[0][0] != '\0'){
	        if (appliquable(act[i].preconds, deb) == TRUE){
	            applique(act[i].add, act[i].delete, deb);
	        }
	        i = i + 1;
	    }
	    i = 0 ;
	}
	printf("AA\n");
	app=appliquable(fin, deb);
	if (!app){
	    printf("\nfaux");
	}
	else{
	    printf("\nvrai");
	}
	printf("\n%s",deb[5]);
	*/
	i = 0;
	int ir = 0;
	int j = 0;
	bool poss = TRUE;
	bool test1 = FALSE;
	bool test2 = FALSE;
	//while(poss && appliquable(fin, deb) == 0)
		while (act[i].preconds[0][0] != '\0' && test1 == FALSE && test2 == FALSE){
			if (appliquable(act[i].preconds, deb) == TRUE){
				test1 = TRUE;
				ir = i;
				j = i;
				i = i + 1;
			}
			else{
				i = i + 1;
			}
		}
		if (test1 == TRUE){
			applique(act[ir].add, act[ir].delete, deb);
		}














	/*Pour implémenter le backtrack, on peut utiliser un indice IR qui indique à
partir de quelle règle on doit chercher une règle applicable dans le
tableau des règles : au départ, cet
indice vaut 0. Si, dans l'exemple donné dans le tableau au-dessus, on
applique la règle 2, puis la
règle 7 et qu'à partir de l'état2 on ne trouve plus de règle
applicable, alors on remonte à l'état1
(l'état2 est oublié) mais IR passe à 8, car on a déjà appliqué la
règle 7 sur l'état 1, et on sait que ça
conduit à une impasse. Puis lorsqu'on trouve une règle d'indice ≥8 à
appliquer sur l'état1, on
l'applique, et IR repasse à 0, car, pour le nouvel état obtenu, on n'a
encore testé aucune règle. Et on
recommence jusqu'à atteindre le but, ou avoir testé toutes les règles
applicables sur tous les chemins
possibles de raisonnement.*/

fclose(start);
}
