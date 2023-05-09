//generation des tuiles
 
#include <stdio.h>
#include <math.h>
#include <stdlib.h>  
#include <unistd.h>
#include <time.h>
#include <sys/time.h>
#include <string.h>
#define ARRAY 7


//nature de la case 
typedef enum {VOID/*0*/ , BASILIC/*1*/, TROLL/*2*/, ZOMBIE/*3*/, HARPY/*4*/, TOTEM/*5*/, CHEST/*6*/, SWORD/*7*/, STAFF/*8*/, SPELLBOOK/*9*/, DAGGER/*10*/, PORTAL /*11*/, SPAWN/*12*/}Type;
typedef enum {TORCH,SHIELD,AXE,BOW}Weapon; //armes équipables
typedef enum {WARRIOR,RANGER,MAGE,THIEF}Class; //classe choisie par le personnage
typedef enum {RED, BLUE, GREEN, YELLOW}Color;
typedef struct {
	Type type; //nature de la case
	int state; //0 si case cachée, 1 sinon
	int player; //0 si personne 1 , 2 , 3 , 4 en fonct° du joueur
}Tile;

typedef struct {
	Weapon weapon; //arme choisie
	Class class; //classe du personnage
	int artifact;//0 si arme antique pas trouvée, 1 sinon
	int chest;//nombre de coffres récupérés: 0, 1 ou 2
	int x;//position du personnage
	int y;
	Color color; //couleur du perso + spawn
}Character;

int scan(char* input){ //fonct° scan pour limiter les bugs juste pour les %c 
	int a=scanf("%c", input);
	while(getchar() != '\n'){}
	return a;
}

int countTiles(int a, int* compteur){//gère le compteur et renvoie 0 si le nombre max de cases d'un certain type est déjà atteint et 1 sinon
  switch(a){
	  case 1: //monstres
		case 2:
		case 3:
		case 4:
        	if(compteur[0]>=16){
            	return 0;
        	}
			compteur[0]++;
			return 1;
		break;
		case 5:
			if (compteur[1]<2){
				compteur[1]++;
            	return 1;
			}
			return 0;
        	break;
		case 6:
			if (compteur[2]<2){
				compteur[2]++;
            	return 1;
			}
  			return 0;
		break;
		case 7:
			if (compteur[3]==0){
				compteur[3]++;
             	return 1;
			}
  			return 0;
		break;
		case 8:
			if (compteur[4]==0){
  				compteur[4]++;
            	return 1;
			}
			return 0;
		break;
		case 9:
			if (compteur[5]==0){
				compteur[5]++;
            	return 1;
			}
			return 0;
		break;
		case 10:
			if (compteur[6]==0){
				compteur[6]++;
            	return 1;
			}
			return 0;
		break;
		case 11:
			if (compteur[7]==0){
				compteur[7]++;
            	return 1;
			}
			return 0;
          	break;
          	default: 
			return 0;
	}
}



void generateTiles(Tile map[][ARRAY]){
	srand( time( NULL ) );
	if (map==NULL){
		exit(1);
	}
	int i,k,j;
	int* compteur=NULL;
	compteur=malloc(8*sizeof(int)); //compte le nombre de : 0=monstres, 1=totems, 2=coffres, 3=épée, 4=baton, 5=grimoire, 6=dague, 7=portail
	if(compteur==NULL){
			exit(1);
	} 
	for (i=0; i<7; i++){
			map[0][i].state=1; //contour du plateau, cases vides=cases révélées
			map[0][i].type=VOID;
	}
	for (i=0; i<7; i++){
			map[6][i].state=1;
			map[6][i].type=VOID;
	}
	for (i=0; i<7; i++){
			map[i][0].state=1;
			map[i][0].type=VOID;
	}
	for (i=0; i<7; i++){
			map[i][6].state=1;
			map[i][6].type=VOID;
	}
	map[0][4].type=SPAWN;
	map[2][0].type=SPAWN;
	map[4][6].type=SPAWN;
	map[6][2].type=SPAWN;
	int a;
	for (i=1; i<6; i++){
		for(k=1;k<6;k++){
			map[i][k].state=0;//cases face cachée
      			a=rand()%11+1;
			map[i][k].type=a; //type de la case
			//compte le nb de cases d'un type sur le plateau; vérifie qu'il y en ait le bon nb ;
	      		while(countTiles(a,compteur)==0) {
              			a=rand()%11+1;
              			map[i][k].type=a;
        		}
    		}
  	}
 /*	for(i=0;i<8;i++){
     		printf("\nCompteur n°%d est à %d.",i,compteur[i]); //vérifie le nombre de tuiles
 	} */
	printf("\n");
}

void viewTiles(Tile map[][ARRAY]){
	int i,k,j;
	printf("\n");
	for (i=0; i<7; i++){
	printf("\n");
		for(k=0;k<7;k++){
			printf(" %d (%d)",map[i][k].type, map[i][k].state);//affiche "nature de la case(statut de la case)" pour toute la map + les bords

		}
	}
	printf("\n");
}

int chooseWeapon(){  //choix d'une arme à chaque tour
		char weapon;
		do{
			printf("Choose a weapon for this turn :\n[1]Torch\n[2]Shield\n[3]Axe\n[4]Bow\n"); //demande tant que réponse incorrecte
			scan(&weapon);
		}while(weapon!=1 && weapon!=2 && weapon!=3 && weapon!=4);
		switch(weapon){
			case '1':
				printf("\nYou choose a torch to light the way.\n"); //renvoie la valeur correspondant à l'arme dans l'enumération Weapon
				return 0;
			break;
			case '2':
				printf("\nYou choose a shield to defend yourself.\n");
				return 1;
			break;
			case '3':
				printf("\nYou choose an axe to cut down monsters.\n");
				return 2;
			break;
			case '4':
				printf("\nYou choose a bow to kill monsters from afar.\n");
				return 3;
			break;
			default:
				exit(2);
			break;
		}
}

int fightMonster(Weapon weapon, Tile monster){
		if (monster.state==1 || monster.type==0 || monster.type>4){
				exit(3); //si tuile déjà explorée ou pas un monstre
		}
		switch (monster.type){
			case 1:  //en fonction du monstre rencontré, vérifie si le joueur a choisi l'arme appropriée : si oui, renvoie 1, continue; sinon, renvoie 0, respawn.
				printf("\nYou encounter a basilic."); 
				if (weapon==SHIELD){
					printf("\nYou reflect the basilic's deadly glare with your shield and successfully defat your foe. Victorious, you move onwards.\n");
					return 1;
				}
				else{
					printf("\nYou fail to defeat the monster and die. Restart at the beginning and end your turn here.\n");
					return 0;
				}
			break;
			case 2:
				printf("\nYou encounter a troll."); 
				if (weapon==AXE){
					printf("\nYou cut down the troll with your axe and successfully defat your foe. Victorious, you move onwards.\n");
					return 1;
				}
				else{
					printf("\nYou fail to defeat the monster and die. Restart at the beginning and end your turn here.\n");
					return 0;
				}
			break;
			case 3:
				printf("\nYou encounter a zombie.");
				if (weapon==TORCH){
					printf("\nYou set the zombie on fire with your torch and successfully defat your foe. Victorious, you move onwards.\n");
					return 1;
				}
				else{
					printf("\nYou fail to defeat the monster and die. Restart at the beginning and end your turn here.\n");
					return 0;
				}
			break;
			case 4:
				printf("\nYou encounter a harpy.");
				if (weapon==BOW){
					printf("\nYou fire an arrow at the harpy from afar with your bow and successfully defat your foe. Victorious, you move onwards.\n");
					return 1;
				}
				else{
					printf("\nYou fail to defeat the monster and die. Restart at the beginning and end your turn here.\n");
					return 0;
				}
			default:
				exit(2);
			break;

		}
}

int legendaryWeapon(Character p, Tile treasure){
	if (treasure.state==1 || treasure.type<7 || treasure.type==11){
		exit(6); //si tuile déjà explorée ou vide ou pas une arme antique
	}
	switch(treasure.type){
		case 7: //épée découverte
			printf("\nYou find the legendary sword of fire.");
			if(p.class==WARRIOR){
				printf("\nAs a warrior, you were looking for this artifact. You take it with you.");
				p.artifact++;
			}
			else{
				printf("\nYou aren't a warrior. Not interested, you leave it there.");
			}
		break;
		case 8: //baton découvert
			printf("\nYou find the legendary familiars' command staff.");
			if(p.class==RANGER){
				printf("\nAs a ranger, you were looking for this artifact. You take it with you.");
				p.artifact++;
			}
			else{
				printf("\nYou aren't a ranger. Not interested, you leave it there.");
			}
		break;
		case 9://grimoire découvert
			printf("\nYou find the legendary spellbook.");
			if(p.class==MAGE){
				printf("\nAs a mage, you were looking for this artifact. You take it with you.");
				p.artifact++;
			}
			else{
				printf("\nYou aren't a mage. Not interested, you leave it there.");
			}
		break;
		case 10: //dague découverte
			printf("\nYou find the legendary dagger of sleep.");
			if(p.class==THIEF){
				printf("\nAs a thief, you were looking for this artifact. You take it with you.");
				p.artifact++;
			}
			else{
				printf("\nYou aren't a thief. Not interested, you leave it there.");
			}
		break;
		default:
			exit(7);
		break;
	}
	printf("\nYou move on.\n");
	return 1;
}

int totemFunction(Tile totem, Tile map[][ARRAY]){
	if (totem.state==1 || totem.type==0 || totem.type!=TOTEM){
		exit(4); //si tuile déjà explorée ou vide ou pas un totem
	}
	char x;
	char y;
	int line, column;
	printf("\nYou find a magical totem glowing ominously. As you feel yourself dying, you are presented with a choice:\n");
	do{
	printf("Choose a tile to exchange the totem with (Line and column numbers):\n");
	scan(&x);
	scan(&y);
	line=atoi(&x);
	column=atoi(&y);
	}while(map[line][column].state==1 || map[line][column].type==VOID ||  map[line-1][column].type==SPAWN || map[line][column-1].type==SPAWN||  map[line+1][column].type==SPAWN || map[line][column+1].type==SPAWN);

	Tile tile;
	tile=map[line][column];
	map[line][column].type=TOTEM;
	totem=tile;
	return 0;
}

int portalFunction(Tile portal, Tile map[][ARRAY], Character p){
	if (portal.state==1 || portal.type==0 || portal.type!=PORTAL){
		exit(4); //si tuile déjà explorée ou vide ou pas un portail
	}
	char x;
	char y;
	int line, column;
	printf("\nYou find a magical portal. As you feel yourself pulled in, you are presented with a choice:\n");
	do{
	printf("Choose a tile to be teleported to (Line and column numbers):\n");
	scan(&x);
	scan(&y);
	line=atoi(&x);
	column=atoi(&y);
	}while(map[line][column].state==1);
	p.x=line;
	p.y=column;
	return 1;
}

int revealTile(Tile tile, Character p, Tile map[][ARRAY]){ //renvoie 0 si fin du tour, 1 sinon
	if (tile.state==1 || tile.type==0 || tile.type==12){
		exit(4); //si tuile déjà explorée ou vide
	}
	printf("\nYou enter a new room.");
	if (tile.type>0 && tile.type<5){
		printf("\nA foe attacks you.");
		return fightMonster(p.weapon, tile); //si tuile=monstre ->appelle fonction fightMonster, renvoie 0 ou 1 si défaite ou victoire
	}
	else if(tile.type>6 && tile.type<11){
		printf("\nYou discover an artifact."); //si tuile=arme antique->appelle fonction legendaryWeapon, renvoie toujours 1, met à jour le profil du personnage du joueur
		return legendaryWeapon(p, tile);  
	}
	switch(tile.type){
		case 5: //totem découvert
			return totemFunction(tile, map); //à finir
		break;
		case 6://coffre découvert
			p.chest++;
			return 1;
		break;
		case 11: //portail découvert
			return portalFunction(tile, map , p);
		break;
		default:
			exit(5);
		break;
	}
}

Character* createCharacters(){ //création des 4 persos
	Character* players;
	players=malloc(4*sizeof(Character));
	if(players==NULL){
		exit(10);
	}
	int i;
	for(i=0; i<4; i++){	
		players[i].artifact=0;
		players[i].chest=0;
	}
	char* class;
	char* color;
	class=malloc(4*sizeof(char));
	color=malloc(4*sizeof(char));
	if(class==NULL){
		exit(10);
	}
	if(color==NULL){
		exit(10);
	}
	int error=0;
	int k;
	int a=0;
	for(i=0; i<4; i++){
		printf("Choose a class for your character:\n[1]Warrior\n[2]Ranger\n[3]Mage\n[4]Thief\n");
		do{	
			a=0;
			error=0;
			printf("\nPlayer n°%d:\n",i+1);
			while (a==0){
				a=scan( &class[i]);
			}
			if(a!=0){
				if (class[i]!='1' && class[i]!='2' && class[i]!='3' && class[i]!='4'){
					error=1;
				}
				if (k!=i){
					for (k=0;k<i;k++){
						if(class[k]==class[i]){
							error=1;
						}
					}
				}
			}
		}while(error);//demande tant que réponse incorrecte ou égale aux joueurs précédents
		switch(class[i]){
			case '1':
				printf("\nYou choose to play as a warrior.\n"); 
				players[i].class=0;
			break;
			case '2':
				printf("\nYou choose to play as a ranger.\n");
				players[i].class=1;
			break;
			case '3':
				printf("\nYou choose to play as a mage.\n");
				players[i].class=2;
			break;
			case '4':
				printf("\nYou choose to play as a thief.\n");
				players[i].class=3;
			break;
			default:
				exit(2);
			break;
		}
	}
	for(i=0; i<4; i++){
		printf("Choose a color for your character:\n[1]Red\n[2]Blue\n[3]Green\n[4]Yellow\n"); //demande tant que réponse incorrecte
		do{
			error=0;
			printf("\nPlayer n°%d:\n",i+1);
			scan (&color[i]);
			if (color[i]!='1' && color[i]!='2' && color[i]!='3' && color[i]!='4'){
				error=1;
			}
			for (k=0;k<i;k++){
				if(color[k]==color[i]){
					error=1;
				}
			}
		}while(error);
		switch(color[i]){
			case '1': 
				players[i].color=0;
			break;
			case '2':
				players[i].color=1;
			break;
			case '3':
				players[i].color=2;
			break;
			case '4':
				players[i].color=3;
			break;
			default:
				exit(2);
			break;
		}
	}	
	return players;
}

void viewCharacters(Character* players){
	if (players==NULL){
		exit(15);
	}
	int i=0;
	for (i=0;i<4;i++){
		switch(players[i].color){
			case 0: 
		/*	printf("\033[0;1m"); en gras  */ 
			printf("\033[01;31m");
			break;
			case 1: 
		/* 	printf("\033[0;4m"); en surligné */
			printf("\033[01;34m");
			break;
			case 2: 
		/*	printf("\033[0;2m"); en plus sombre (gris?) */
			printf("\033[01;32m");
			break;
			case 3: 
		/*	printf("\033[0;3m"); en italiques */
			printf("\033[01;33m"); 
			break;
		}
		printf("\nPlayer n°%d:\n",i+1);
		printf("Class: ");
		switch(players[i].class){
			case 0: 
			printf("Warrior.");
			break;
			case 1: 
			printf("Ranger.");
			break;
			case 2: 
			printf("Mage.");
			break;
			case 3: 
			printf("Thief.");
			break;
		}
	
		
		if (players[i].artifact){
			printf("\nArtifact found.");
		}
		else{
			printf("\nArtifact not found.");
		}
		printf("\nNumber of chests found : %d.",players[i].chest); 
		printf("\033[00m");
	
	}
	printf("\n");

}	

int main (){
 	Tile map[ARRAY][ARRAY];
 	generateTiles(map);//tab de 7*7 cases
 	viewTiles(map);
 	Character* players;
 	players=malloc(4*sizeof(Character));
	if(players==NULL){
		exit(10);
	}
	players=createCharacters();
	viewCharacters(players);
 	return 0;
}
