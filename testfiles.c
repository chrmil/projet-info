#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <errno.h>
#define SIZE 15
#define ARRAY 7						// 7x7 cases
#define SIZEX 62					// 9 longueur case
#define SIZEY 34					// 5 hauteur case

typedef struct Score{
	char nom[50];
	int pts;
}score;

void printMapRec(int a, int b, char tab[][ARRAY]){	// fonction dessine map
	if (a>53 || a<9 || b>29 || b<5){		// si cases du bord
		if(a>53 && b<25 && b>19){
			printf("\033[0;41m");		// fond rouge (start haut gauche)
		}
		else if(a<45 && a>35 && b<5){
			printf("\033[0;42m");		// fond vert (start bas gauche)
		}
		else if(a<9 && b<15 && b>9){
			printf("\033[0;43m");		// fond jaune (start bas droit)
		}
		else if(a<27 && a>17 && b>29){
			printf("\033[0;44m");		// fond bleu (start haut droit)
		}
		else{
			printf("\033[0m");		// pas de fond
		}
	}
	else if (((a/9)-(b/5))%2 == 0){
		printf("\033[0;40m");			// fond noir
	}
	else{
		printf("\033[0;47m");			// fond blanc
	}
	if (a>=0){
		printf(" ");
		printMapRec(a-1, b, tab);		// print une ligne
	}
	else if (b>0){
		printf("\033[0m");			// fin
		printf("\n");
		printMapRec(SIZEX, b-1, tab);		// changement de ligne
	}
	else{
		printf("\n");
		printf("\033[0m");			// fin
	}
}

void printMap(char tab[][ARRAY]){			// appel fonction dessine map
	//printf("\033[1;30m");				// écriture en noir
	printf("\n");
	printMapRec(SIZEX, SIZEY, tab);
}
/*
int main(int argc, char** argv){
	srand(time(NULL));
	char map[ARRAY][ARRAY] ={0};
	printMap(map);
	return 0;
}
*/
/*
Couleurs
printf("\033[x;yzm");
x (0 normal, 1 bold, 2 darker, 3 italic, 4 underligned,  5 boop beep)
y (3 txt, 4bg)
z (0 black, 1 red, 2 green, 3 yellow, 4 blue, 5 purple, 6 cyan, 7 white)
*/

void comp(){
  
}

int main(int argc, char **argv) {
	srand(time(NULL));
	score a;
	a.pts = 0;
	a.nom[50] = {'_'};
	char map[ARRAY][ARRAY], tab[SIZE], menu, nom[50] = {'_'};
	int i = 0;
	char* t;
	FILE *f;
	printf("Entrez 'j' pour jouer, 'c' pour voir le classement, 'f' pour fermer l'exécutable\n");
	scanf("%c", &menu);
	switch(menu){
		case 'j':
			printMap(map);
			printf("Entrez un pseudo: ");
			scanf("%s", a.nom);
			printf("Entrez un score: ");
			scanf("%d", &a.pts);
			f = fopen("test.txt", "a+");					// ouverture fichier
			if (f == NULL) {						// si pas ouvert
				printf("Ouverture du fichier impossible\n");
				printf("code d'erreur = %d \n", errno);
				printf("Message d'erreur = %s \n", strerror(errno));
				exit(1);
			}
			t = fgets(tab, SIZE-1, f);					// lecture fichier
			if (t == NULL){							// si échec lecture
				printf("Echec lecture du classement\n");
			}
			fprintf(f, "\n%10d\n%10.10s", a.pts, a.nom);
			fclose(f);
		break;
		case 'c':
			f = fopen("test.txt", "a+");					// ouverture fichier
			if (f == NULL) {						// si pas ouvert
				printf("Ouverture du fichier impossible\n");
				printf("code d'erreur = %d \n", errno);
				printf("Message d'erreur = %s \n", strerror(errno));
				exit(1);
			}
			t = fgets(tab, SIZE-1, f);
			if (t == NULL){							// si échec lecture
				printf("Echec lecture du classement\n");
			}
			while(i <= 20 && t != NULL){
				t = fgets(tab, SIZE-1, f);					// lecture fichier
				if (t == NULL){							// si échec lecture
					printf("Echec lecture du classement\n");
				}
				printf("%s\n", tab);
				i++;
			}
			fclose(f);
		break;
		default:
			printf("Entrée incorrecte\n");
		case 'f':
			printf("Fin de l'exécution\n");
		break;
	}
	return 0;
}
