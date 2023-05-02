#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#define SIZE 12						// 10 characters + \n + EOF or \0
#define ARRAY 7						// 7x7 cells map
#define SIZEX 62					// 9 width cells (63 between 0 and 62)
#define SIZEY 34					// 5 height cells (35 between 0 and 34)

typedef struct Player{					// Structure player stats
	char name[SIZE];
	int pts;
}pl;

void printMapRec(int a, int b, char tab[][ARRAY]){	// map drawing function
	if (a>53 || a<9 || b>29 || b<5){		// edges of map
		if(a>53 && b<25 && b>19){
			printf("\033[0;41m");		// red spawner
		}
		else if(a<45 && a>35 && b<5){
			printf("\033[0;42m");		// green spawner
		}
		else if(a<9 && b<15 && b>9){
			printf("\033[0;43m");		// yellow spawner
		}
		else if(a<27 && a>17 && b>29){
			printf("\033[0;44m");		// blue spawner
		}
		else{
			printf("\033[0m");		// nothing
		}
	}
	else if (((a/9)-(b/5))%2 == 0){
		printf("\033[0;40m");			// black cells
	}
	else{
		printf("\033[0;47m");			// white cells
	}
	if (a>=0){
		printf(" ");
		printMapRec(a-1, b, tab);		// print line
	}
	else if (b>0){
		printf("\033[0m");			// end of line
		printf("\n");
		printMapRec(SIZEX, b-1, tab);		// newline
	}
	else{
		printf("\n");
		printf("\033[0m");			// end of function
	}
}

void printMap(char tab[][ARRAY]){			// calls map drawing function
	printf("\n");
	printMapRec(SIZEX, SIZEY, tab);
}

/*
Couleurs
printf("\033[x;yzm");
x (0 normal, 1 bold, 2 darker, 3 italic, 4 underligned,  5 boop beep)
y (3 txt, 4bg)
z (0 black, 1 red, 2 green, 3 yellow, 4 blue, 5 purple, 6 cyan, 7 white)
*/

void play(){								// function shows map and asks for user and score
	char back;
	pl s;
	s.pts = 0;
	FILE *f = NULL;
	char map[ARRAY][ARRAY];
	printMap(map);
	printf("Input an username: ");
	scanf("\n%[^\n]s", s.name);					// \n ignores newline from last input
	printf("Input a score: ");
	scanf("%d", &s.pts);
	if (s.pts <= -1){						// if the score is too high
		s.pts = -1;
	}
	f = fopen("test.txt", "a+");					// open file
	if (f == NULL) {						// open failed
		printf("Failed to open the file\n");
		printf("Error code = %d \n", errno);
		printf("Error message = %s \n", strerror(errno));
		exit(1);
	}
	fprintf(f, "%10d\n%10.10s\n", s.pts, s.name);
	fclose(f);
	printf("Game ended, input anything to go back to the menu\n");
	scanf("\n%[^\n]s", &back);
	menu();
}

void rank(){								// function shows the rankings
	FILE* f = NULL;
	char* t = NULL;
	char tab[SIZE], back;
	int i = 0;
	f = fopen("test.txt", "a+");					// open file
	if (f == NULL) {						// open failed
		printf("Failed to open the file\n");
		printf("Error code = %d \n", errno);
		printf("Error message = %s \n", strerror(errno));
		exit(1);
	}
	t = fgets(tab, SIZE, f);
	if (t == NULL){							// read failed
		printf("Failed to show the rankings\n");
	}
	while(i <= 20 && t != NULL){
		printf("   Score : %s", tab);
		i++;
		t = fgets(tab, SIZE, f);				// read file
		printf("Username : %s\n", tab);
		i++;
		t = fgets(tab, SIZE, f);				// read file
	}
	fclose(f);
	printf("Input anything to go back to the menu\n");
	scanf("\n%[^\n]s", &back);
	menu();

}

void menu(){											// function shows the menu
	char choice;
	printf("Input 'p' to play, 'r' to check the rankings, 'c' to close the game\n");
	scanf("\n%[^\n]s", &choice);								// [^\n] doesn't stop at spaces
	switch(choice){
		case 'p':
			play();
		break;
		case 'r':
			rank();
		break;
		case 'c':
			printf("Game closed\n");
		break;
		default:
			printf("Incorrect input\n");
			menu();
		break;
	}
}

int main(int argc, char **argv) {
	srand(time(NULL));
	menu();
	return 0;
}
