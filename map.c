#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <unistd.h>
#define ARRAY 7						// 7x7 cases
#define SIZEX 62					// 9 longueur case
#define SIZEY 34					// 5 hauteur case

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

int main(int argc, char** argv){
	srand(time(NULL));
	char tab[ARRAY][ARRAY] ={0};
	printMap(tab);
	return 0;
}

/* Couleurs
printf("\033[x;yzm");
x (0 normal, 1 bold, 2 darker, 3 italic, 4 underligned,  5 boop beep)
y (3 txt, 4bg)
z (0 black, 1 red, 2 green, 3 yellow, 4 blue, 5 purple, 6 cyan, 7 white)
*/
