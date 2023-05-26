#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#define SIZE 12						// 10 characters + \n or EOF + \0
#define ARRAY 7						// 7x7 cells map (including spawns)
#define SIZEX 62					// 9 width cells (63 between 0 and 62)
#define SIZEY 34					// 5 height cells (35 between 0 and 34)

typedef enum Monstertype{VOID/*0*/, BASILIC/*1*/, TROLL/*2*/, ZOMBIE/*3*/, HARPY/*4*/, TOTEM/*5*/, CHEST/*6*/, SWORD/*7*/, STAFF/*8*/, SPELLBOOK/*9*/, DAGGER/*10*/, PORTAL /*11*/, SPAWN/*12*/}Type;								// monster types
typedef enum Weapontype{NOTHING,TORCH,SHIELD,AXE,BOW}Weapon;	// choosable weapons
typedef enum Playerclass{WARRIOR,RANGER,MAGE,THIEF}Class;	// player classes
typedef enum Playercolor{RED, BLUE, GREEN, YELLOW}Color;	// player color
typedef struct Playercoordinates{
	int x;
	int y;
}Coordinates;			// coordinates
typedef struct Tiletype{
	Coordinates position;	//coordonnées de la tuile
	Type type;		//nature de la case
	int state;		//0 si case cachée, 1 sinon
	int player;		//0 si personne 1 , 2 , 3 , 4 en fonct° du joueur
}Tile;				// tile type
typedef struct Characterstats{
	Coordinates position;	// position du personnage
	Coordinates spawn;	// coordonées du spawn
	Coordinates* tiles;	// tableau des coordonnées de toutes les tuiles retournées par le joueur en un tour
	Color color;		// couleur du perso + spawn
	Weapon weapon;		// arme choisie
	Class class;		// classe du personnage
	int artifact;		// 0 si arme antique pas trouvée, 1 sinon
	int chest;		// nombre de coffres récupérés: 0, 1 ou 2
	int treasure;		// total amount of treasures found during the game
	int monsters;		// amount of monsters defeated during the game
	int win;		// whether the player won or not
	int exploration;	// amount of revealed tiles during the game
	int pts;			// à retirer
	char name[10];		// 10 characters name
}Character;			// player stats (Christelle)

// Christelle
int countTiles(int a, int* compteur);						// gère le compteur et renvoie 0 si le nombre max de cases d'un certain type est déjà atteint et 1 sinon
void generateTiles(Tile map[][ARRAY]);						// random map generator
void viewTiles(Tile map[][ARRAY]);						// check type of tile
void chooseWeapon(Character* p);						// choix d'une arme à chaque tuile
int fightMonster(Character* p, Tile* monster);					// fight when monster encountered
int legendaryWeapon(Character* p, Tile* treasure);				// found legendary weapon, checks if it's the player's or not
int totemFunction(Tile* totem, Tile map[][ARRAY]);				// found a totem
int portalFunction(Tile* portal, Tile map[][ARRAY], Character* p, int i);	// found a portal
int revealTile(Tile* tile, Character* p, Tile map[][ARRAY], int i);		// renvoie 0 si fin du tour, 1 sinon
Character* createCharacters(Character* players, int nbp);			// création des 4 persos
void viewCharacter(Character player,int i);					// view each character's stats
int victory(Character* p,int i); 						// check if victor
int playerTurn(Tile map[][ARRAY], Character p, int i);				// tour d'un joueur
void playGame(char nbp, Character* players);					// gestion d'une partie

// Adrien
void viewPosition(Character p);							// Procédure pour voir la position d'un joueur
void countTilesReveal(Tile map[][ARRAY]);					// Compter les cases déjà révélées
void move(Character* p, Tile map[][ARRAY],int i);				// Procédure pour les déplacements d'un joueur
int stuck(Character* p, Tile map[][ARRAY]);					// if the player is stuck

// Florian
int scan(char* input);								// scanf but deletes the end
char sortTab(Character tab[], char size);					// sorted tab verification
void merge(Character tab[], char begin, char middle, char end, char size);	// mergesort Christelle 1
void mergeSortRec(Character tab[], char begin, char end, char size);		// mergesort Christelle 2
void mergeSort(Character tab[], char size);					// mergesort call
void sortRanks(FILE* f, char k);						// sorts the rankings from highest to lowest scores
char addScores(FILE* f, Character* s, char plrnb);				// hecks if name was already registered and prints scores accordingly
void finish(char plrnb, Character* s);						// end of game
void printMapRec(int a, int b, char tab[][ARRAY], char i);			// map drawing
void printMap();								// map drawing call
void game(char plrnb, Character* s);						// game
void start();									// asks for the initial player infos
void play();										// unfinished
void rank();									// shows the rankings
void menu();									// shows the menu
