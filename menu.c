#include "library.h"

int scan(char* input){							// scanf function but deletes the end
	int a=scanf("%c", input);
	while(getchar() != '\n'){}
	return a;
}

char sortTab(Character tab[], char size){					// sorted tab verification
	char i;
	for (i=0;i<size-1;i++){
		if (tab[i].win<tab[i+1].win){
			return 0;
		}
	}
	return 1;
}

void merge(Character tab[], char begin, char middle, char end, char size){	// mergesort Christelle
	char i,k,j;
	Character* tab2 = NULL;
	tab2 = malloc(size * sizeof(Character));
	if (tab2 == NULL){
		printf("Failed to allocate for Character* tab2 (func merge)");
		exit(61);
	}
	k=begin;
	j=end;
	for (i=begin; i<middle+1;i++){
		tab2[i]=tab[i];
	}
	for (i=middle+1; i<end+1;i++){
		tab2[i]=tab[end-i+middle+1];
	}
	for (i=begin; i<end+1; i++){
		if(tab2[k].pts>=tab2[j].pts){
			tab[i]=tab2[k];
			k++;
		}
		else{
			tab[i]=tab2[j];
			j--;
		}
	}
}

void mergeSortRec(Character tab[], char begin, char end, char size){	// mergesort function
	char middle;
	if (begin<end){
		middle=(begin+end)/2;					// cuts the tab in half
		mergeSortRec(tab, begin, middle, size);
		mergeSortRec(tab, middle+1, end, size);
		merge(tab, begin, middle, end, size);			// merges the tabs
	}
}

void mergeSort(Character tab[], char size){				// mergesort function call
	if (sortTab(tab, size)){
		return;
	}
	mergeSortRec(tab, 0, size-1, size);
}

void sortRanks(FILE* f, char k){					// function sorts the rankings from highest to lowest scores
	char i;
	Character* sort = NULL;
	sort = malloc(k * sizeof(Character));
	if (sort == NULL){
		printf("Failed to allocate for Character* sort (func sortRanks)");
		exit(51);
	}
	rewind(f);
	for (i = 0; i < k; i++){					// group the rankings in a tab
		fscanf(f, " %d %d %d %d", &sort[i].win, &sort[i].treasure, &sort[i].monsters, &sort[i].exploration);
		fscanf(f, "\n%[^\n]s", sort[i].name);
	}
	mergeSort(sort, k);						// sort the tab
	rewind(f);
	for (i = 0; i < k; i++){					// print the sorted tab
		fprintf(f, "%10d %10d %10d %10d %10d %10.10s\n", sort[i].win, sort[i].treasure, sort[i].monsters, sort[i].exploration, sort[i].name);
	}
	free(sort);
}

char addScores(FILE* f, Character* s, char plrnb){				// function checks if name was already registered and prints scores accordingly
	short t = 0;							// return of fscanf
	char i, j, k = 0, ls, lrank, *a = NULL, *b = NULL;
	Character rank;
	a = malloc(plrnb * sizeof(char));
	if (a == NULL){
		printf("Failed to allocate for char* a (func addScores)");
		exit(42);
	}
	b = calloc(plrnb, sizeof(char));
	if (b == NULL){
		printf("Failed to allocate for char* b (func addScores)");
		exit(42);
	}
	t = fscanf(f, " %d %d %d %d", &rank.win, &rank.treasure, &rank.monsters, &rank.exploration);				// read file
	while(t != EOF){						// compares the names
		k++;
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
				rank.pts += s[i].win;
				fseek(f, -21, SEEK_CUR);
				fprintf(f, "%10d %10d %10d %10d", rank.win, rank.treasure, rank.monsters, rank.exploration);
				fseek(f, 11, SEEK_CUR);
				b[i] = 1;
			}
		}
		t = fscanf(f, " %d %d %d %d", &rank.win, &rank.treasure, &rank.monsters, &rank.exploration);	
	}
	while(getchar() != '\n'){}					// clears buffer
	for (i = 0; i < plrnb; i++){					// print scores in file if player name doesn't exist yet
		if (b[i] == 0){
			k++;
			fprintf(f, "%10d %10d %10d %10d %10.10s\n", s[i].win, s[i].treasure, s[i].monsters, s[i].exploration, s[i].name);
		}
	}
	free(a);
	free(b);
	return k;
}

void finish(char plrnb, Character* s){		// end of game
	char back = '0', k;

	FILE* f = NULL;
	f = fopen("score.txt", "r+");					// open file
	if (f == NULL) {						// open failed
		printf("Failed to open the file\n");
		printf("Error code = %d \n", errno);
		printf("Error message = %s \n", strerror(errno));
		exit(30);
	}
	k = addScores(f, s, plrnb);
	sortRanks(f, k);
	fclose(f);
	
	while(getchar() != '\n'){}
	printf("Game ended\nInput 'r' to replay with the same players\nInput anything else to go back to the menu\n");
	scan(&back);					// asks to replay with the same players
	printf("%c\n", back);
	switch(back){
		case 'r':
			printf("\nRestarting game...\n");
			playGame(plrnb, s);
		break;
		default:
			menu();
		break;
	}
}

void printMapRec(int a, int b, char tab[][ARRAY], char i){	// map drawing function
	if (a>53 || a<9 || b>29 || b<5){			// edges of map
		if(a>53 && b<25 && b>19){
			printf("\033[0;41m");			// red spawner (top left)
		}
		else if(a<45 && a>35 && b<5){
			printf("\033[0;42m");			// green spawner (bottom left)
		}
		else if(a<9 && b<15 && b>9){
			printf("\033[0;43m");			// yellow spawner (bottom right)
		}
		else if(a<27 && a>17 && b>29){
			printf("\033[0;44m");			// blue spawner (top right)
		}
		else{
			printf("\033[0m");			// nothing
		}
	}
	else if (((a/9)-(b/5))%2 == 0){
		printf("\033[0;40m");				// black cells
	}
	else{
		printf("\033[0;47m");				// white cells
	}
	if (a>=0){
		if (a%9 == 4 && b == 32){
			printf("%d", i);			// print column number
			i++;
			printMapRec(a-1, b, tab, i);		// print line
		}
		else if (a == 58 && b%5 == 2){
			printf("%d", i);			// print line number
			i++;
			printMapRec(a-1, b, tab, i);		// print line
		}
		else{
			printf(" ");
			printMapRec(a-1, b, tab, i);		// print line
		}
	}
	else if (b>0){
		printf("\033[0m");				// end of line
		printf("\n");
		if (i == 7){
			i = 1;
		}
		printMapRec(SIZEX, b-1, tab, i);		// newline
	}
	else{
		printf("\n");
		printf("\033[0m");				// end of function
	}
}

void printMap(){			// calls map drawing function
	char tab[ARRAY][ARRAY];
	printf("\n");
	printMapRec(SIZEX, SIZEY, tab, 0);
}

/*
Colours
printf("\033[x;yzm");
x (0 normal, 1 bold, 2 darker, 3 italic, 4 underligned,  5 boop beep)
y (3 txt, 4bg)
z (0 black, 1 red, 2 green, 3 yellow, 4 blue, 5 purple, 6 cyan, 7 white)
*/

void start(){																// function asks for the initial player infos
	char back, plrnb, role, i, j, k, ls, lk, a, b;
	Character* s = NULL;
	printf("Input the number of players in the game (between 2 and 4)\n");				// number of players
	scan(&plrnb);
	while(plrnb > '4' || plrnb < '2'){
		printf("Incorrect input\nInput the total number of players in the game (between 2 and 4)\n");
		scan(&plrnb);
	}
	plrnb -= 48;
	s = malloc(plrnb * sizeof(Character));				// username inputs (human only)
	if (s == NULL){
		printf("Failed to allocate for Character* s (func start)");
		exit(21);
	}
	for (i = 0; i < plrnb; i++){
		printf("Input P%d's username: ", i+1);
		scanf("\n%[^\n]s", s[i].name);
		while(getchar() != '\n'){}
		ls = strlen(s[i].name);
		for (j = 0; j < ls; j++){
			if (s[i].name[j] <= 'z' && s[i].name[j] >= 'a'){
				s[i].name[j] -= 32;
			}
		}
		for (k = 0; k < i; k++){				// checks if two players have the same username
			a = 0;
			lk = strlen(s[k].name);
			if (ls != lk){					// compares name length
				a = 1;
			}
			else{
				for (j = 0; j < ls; j++){		// compares each character
					if (s[i].name[j] != s[k].name[j]){
						a = 1;
					}
				}
			}
			if (a == 0){
				b = 1;
			}
		}
		if (b == 1){						// redoes if the username is the same as another player's
			i--;
			printf("Username is already taken\n");
			b = 0;
		}
	}
	playGame(plrnb, s);
}

void play(){								// unfinished function
	char choice;
	if (NULL){							// if there is a saved file
		printf("Saved data was found, input 's', to continue the game\nInput 'n' to start a new game (saved data will be erased)\nInput 'm' to go back to the menu\n");
		scan(&choice);
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
		scan(&choice);
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
	f = fopen("score.txt", "r");					// open file
	if (f == NULL) {						// open failed
		printf("Failed to open the file\n");
		printf("Error code = %d \n", errno);
		printf("Error message = %s \n", strerror(errno));
		exit(10);
	}
	t = fgets(tab, SIZE, f);					// read file
	if (t == NULL){							// read failed
		printf("Failed to show the rankings\n");
	}
	while(i <= 18 && t != NULL){					// reads the first 10 players
		printf("Score : %s", tab);
		t = fgets(tab, SIZE, f);
		printf("Username : %s", tab);
		i += 2;
		t = fgets(tab, SIZE, f);
	}
	fclose(f);
	printf("Input anything to go back to the menu\n");
	scan(&back);
	menu();

}

void menu(){								// function shows the menu
	char choice;
	printf("\033[2J");
	printf("\033[1;1H");
	printf("Input 'p' to play\nInput 'r' to check the rankings\nInput 'c' to close the game\n");
	scan(&choice);
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
			menu();
		break;
	}
}

int main(){
	srand(time(NULL));
	menu();
	return 0;
}

