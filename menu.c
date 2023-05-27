#include "library.h"

int scan(char* input){							// scanf function but deletes the end
	int a=scanf("%c", input);
	while(getchar() != '\n'){}
	return a;
}

char sortTab(Character tab[], char size){				// sorted tab verification
	char i;
	for (i=0;i<size-1;i++){
		if (tab[i].win < tab[i+1].win){			// if win count isn't sorted
			return 0;
		}
		else if (tab[i].win == tab[i+1].win){
			if (tab[i].treasure < tab[i+1].treasure){	// if treasures found count isn't sorted
				return 0;
			}
			else if (tab[i].treasure == tab[i+1].treasure){
				if (tab[i].monsters < tab[i+1].monsters){	// if defeated monsters count isn't sorted
					return 0;
				}
				else if (tab[i].monsters == tab[i+1].monsters){
					if (tab[i].exploration < tab[i+1].exploration){	// if revealed tiles count isn't sorted
						return 0;
					}
				}
			}
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
		if(tab2[k].win>tab2[j].win){			// sorts by win count
			tab[i]=tab2[k];
			k++;
		}
		else if(tab2[k].win==tab2[j].win){
			if(tab2[k].treasure>tab2[j].treasure){		// sorts by number of treasures found
				tab[i]=tab2[k];
				k++;
			}
			else if(tab2[k].treasure==tab2[j].treasure){
				if(tab2[k].monsters>tab2[j].monsters){		// sorts by monsters defeated
					tab[i]=tab2[k];
					k++;
				}
				else if(tab2[k].monsters==tab2[j].monsters){
					if(tab2[k].exploration>=tab2[j].exploration){	// sorts by tiles revealed
						tab[i]=tab2[k];
						k++;
					}
					else{
						tab[i]=tab2[j];
						j--;
					}
				}
				else{
					tab[i]=tab2[j];
					j--;
				}
			}
			else{
				tab[i]=tab2[j];
				j--;
			}
		}
		else{
			tab[i]=tab2[j];
			j--;
		}
	}
	free(tab2);
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
	if (sortTab(tab, size)){					// stops the function if the rankings are correctly sorted
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
		fprintf(f, "%10d %10d %10d %10d %10.10s\n", sort[i].win, sort[i].treasure, sort[i].monsters, sort[i].exploration, sort[i].name);
	}
	free(sort);
}

char addScores(FILE* f, Character* s, char plrnb){			// function checks if name was already registered and prints scores accordingly
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
	t = fscanf(f, " %d", &rank.win);									// read file
	while(t != EOF){											// compares the names
		t = fscanf(f, " %d %d %d", &rank.treasure, &rank.monsters, &rank.exploration);			// read file
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
				rank.win += s[i].win;
				rank.treasure += s[i].treasure;
				rank.monsters += s[i].monsters;
				rank.exploration += s[i].exploration;
				fseek(f, -51, SEEK_CUR);
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
	while(getchar()!= '\n'){}
	printf("Game ended\nInput 'r' to replay with the same players\nInput anything else to go back to the menu\n");
	scan(&back);					// asks to replay with the same players
	printf("%c\n", back);
	switch(back){
		case 'r':
			printf("\nRestarting game...\n");
			sleep(1);
			playGame(plrnb, s);
		break;
		default:
			free(s);
			menu();
		break;
	}
}

void start(){																// function asks for the initial player infos
	char back, plrnb, i, j, k, ls, lk, a, b;
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
	while(getchar() != '\n'){}
	playGame(plrnb, s);
}

void play(){
	char choice;
	printf("Input 'n' to start a new game\nInput 'm' to go back to the menu\n");
	scan(&choice);
	switch(choice){
		case 'n':
			start();		// starts a game
		break;
		case 'm':
			menu();			// back to the menu
		break;
		default:
			printf("Incorrect input\n");
			play();
		break;
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
		printf("Wins : %s", tab);
		t = fgets(tab, SIZE, f);
		printf("    Treasures found : %s", tab);
		t = fgets(tab, SIZE, f);
		printf("    Monsters defeated : %s", tab);
		t = fgets(tab, SIZE, f);
		printf("    Revealed tiles : %s", tab);
		t = fgets(tab, SIZE, f);
		printf("    Username : %s", tab);
		t = fgets(tab, SIZE, f);
		i+=2;
	}
	fclose(f);
	printf("\nInput anything to go back to the menu\n");
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
	menu();
	return 0;
}

