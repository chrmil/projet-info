#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#define SIZE 12						// 10 characters + \n or EOF + \0
#define ARRAY 7						// 7x7 cells map
#define SIZEX 62					// 9 width cells (63 between 0 and 62)
#define SIZEY 34					// 5 height cells (35 between 0 and 34)

typedef struct Player{					// structure player stats
	char name[10];					// 10 characters name
	int pts;
}pl;

void finish(char plrnb, pl* s){						// end of game
	short t = 0;							// return of fscanf
	char i, j, ls, lrank, back, tab[SIZE], *a = NULL, *b = NULL;
	pl rank;
	FILE* f = NULL;
	a = malloc(plrnb * sizeof(char));
	if (a == NULL){
		printf("Failed to allocate for char *a (func finish)");
		exit(2);
	}
	b = calloc(plrnb, sizeof(char));
	if (b == NULL){
		printf("Failed to allocate for char *b (func finish)");
		exit(3);
	}
	f = fopen("test.txt", "r+");					// open file
	if (f == NULL) {						// open failed
		printf("Failed to open the file\n");
		printf("Error code = %d \n", errno);
		printf("Error message = %s \n", strerror(errno));
		exit(1);
	}
	t = fscanf(f, " %d", &rank.pts);				// read file
	while(t != EOF){						// compares the names
		t = fscanf(f, "\n%[^\n]s", rank.name);
		for (i = 0; i < plrnb; i++){
			a[i] = 0;
			ls = strlen(s[i].name);
			lrank = strlen(rank.name);
			if (ls != lrank){				// compares name length
				a[i] = 1;
			}
			else{
				for (j = 0; j < ls; j++){		// compares each character
					if (s[i].name[j] != rank.name[j]){
						a[i] = 1;
					}
				}
			}
			if (a[i] == 0){					// adds the new score to the player's total score
				rank.pts += s[i].pts;
				fseek(f, -21, SEEK_CUR);
				fprintf(f, "%10d", rank.pts);
				fseek(f, 21, SEEK_CUR);
				b[i] = 1;
			}
		}
		t = fscanf(f, " %d", &rank.pts);
	}
	for (i = 0; i < plrnb; i++){					// print scores in file if player name doesn't exist yet
		if (b[i] == 0){
			fprintf(f, "%10d\n%10.10s\n", s[i].pts, s[i].name);
		}
	}
	fclose(f);
	printf("Game ended, input anything to go back to the menu\n");
	scanf("\n%[^\n]c", &back);
	menu();
}

void printMapRec(int a, int b, char tab[][ARRAY]){	// map drawing function
	if (a>53 || a<9 || b>29 || b<5){		// edges of map
		if(a>53 && b<25 && b>19){
			printf("\033[0;41m");		// red spawner (top left)
		}
		else if(a<45 && a>35 && b<5){
			printf("\033[0;42m");		// green spawner (bottom left)
		}
		else if(a<9 && b<15 && b>9){
			printf("\033[0;43m");		// yellow spawner (bottom right)
		}
		else if(a<27 && a>17 && b>29){
			printf("\033[0;44m");		// blue spawner (top right)
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

void printMap(){			// calls map drawing function
	char tab[ARRAY][ARRAY];
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

void game(char plrnb, char botnb, pl* s, char level[]){		// game function
	char i;
	printMap();
	for (i = 0; i < plrnb; i++){
		printf("Input P%d's score: ", i+1);
		scanf(" %d", &s[i].pts);
		if (s[i].pts <= -1){				// if the score is too high
			s[i].pts = -1;
		}
	}
	finish(plrnb, s);
}

void start(){																// function asks for the initial player infos
	char back, total, totalnb, plr, plrnb, botnb, i, level[4];
	pl* s;
	printf("Input the total number of players in the game (between 2 and 4, humans and bots included)\n");				// total number of players (humans and bots)
	scanf("\n%[^\n]c", &total);
	while(total > '4' || total < '2'){
		printf("Incorrect input\nInput the total number of players in the game (between 2 and 4, humans and bots included)\n");
		scanf("\n%[^\n]c", &total);
	}
	printf("\nInput the number of human players in the game (between 0 and %c, the other players will be bots)\n", total);		// number of human players
	scanf("\n%[^\n]c", &plr);
	while(plr > total || plr < '0'){
		printf("Incorrect input\nInput the number of human players in the game (between 0 and %c, the other players will be bots)\n", total);
		scanf("\n%[^\n]c", &plr);
	}
	totalnb = atoi(&total);
	plrnb = atoi(&plr);
	botnb = total - plr;
	if (plrnb){															// username inputs (human only)
		s = malloc(plrnb * sizeof(pl));
		if (s == NULL){
			printf("Failed to allocate for pl* s (func start)");
			exit(1);
		}
		for (i = 0; i < plrnb; i++){
			printf("Input P%d's username: ", i+1);
			scanf("\n%[^\n]s", s[i].name);
		}
	}
	if (botnb){															// bot level inputs
		for (i = 0; i < botnb; i++){
			printf("Input Bot%d's level: ", i+1);
			scanf("\n%[^\n]c", &level[i]);
		}
	}
	game(plrnb, botnb, s, level);
}

void play(){
	char choice;
	if (NULL){							// if there is a saved file
		printf("Saved data was found, input 's', to continue the game\nInput 'n' to start a new game (saved data will be erased)\nInput 'm' to go back to the menu\n");
		scanf("\n%[^\n]s", &choice);
		switch(choice){
			case 's':					// will be added later
			break;
			case 'n':
				start();
			break;
			case 'm':
				menu();
			break;
			default:
				printf("Incorrect input\n");
				play();
			break;
		}
	}
	else{								// if there is no saved file
		printf("Input 'n' to start a new game\nInput 'm' to go back to the menu\n");
		scanf("\n%[^\n]s", &choice);
		switch(choice){
			case 'n':
				start();
			break;
			case 'm':
				menu();
			break;
			default:
				printf("Incorrect input\n");
				play();
			break;
		}
	}
}

void rank(){								// function shows the rankings
	FILE* f = NULL;
	char* t = NULL;
	char tab[SIZE], back;
	char i = 0;
	f = fopen("test.txt", "a+");					// open file
	if (f == NULL) {						// open failed
		printf("Failed to open the file\n");
		printf("Error code = %d \n", errno);
		printf("Error message = %s \n", strerror(errno));
		exit(1);
	}
	t = fgets(tab, SIZE, f);					// read file
	if (t == NULL){							// read failed
		printf("Failed to show the rankings\n");
	}
	while(i <= 18 && t != NULL){					// reads the first 10 players
		printf("   Score : %s", tab);
		t = fgets(tab, SIZE, f);
		printf("Username : %s\n", tab);
		i += 2;
		t = fgets(tab, SIZE, f);
	}
	fclose(f);
	printf("Input anything to go back to the menu\n");
	scanf("\n%[^\n]c", &back);
	menu();

}

void menu(){									// function shows the menu
	char choice;
	printf("Input 'p' to play\nInput 'r' to check the rankings\nInput 'c' to close the game\n");
	scanf("\n%[^\n]c", &choice);						// \n ignores newline from last input, [^\n] doesn't stop at spaces
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
