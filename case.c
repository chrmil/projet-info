//generation des tuiles et persos + gestion d'une partie 
 
#include <stdio.h>
#include <math.h>
#include <stdlib.h>  
#include <unistd.h>
#include <time.h>
#include <sys/time.h>
#include <string.h>
#define ARRAY 7

typedef struct{
	int x;
	int y;
}Coordinates;

//nature de la case 
typedef enum {VOID/*0*/ , BASILIC/*1*/, TROLL/*2*/, ZOMBIE/*3*/, HARPY/*4*/, TOTEM/*5*/, CHEST/*6*/, SWORD/*7*/, STAFF/*8*/, SPELLBOOK/*9*/, DAGGER/*10*/, PORTAL /*11*/, SPAWN/*12*/}Type;
typedef enum {NOTHING,TORCH,SHIELD,AXE,BOW}Weapon; //armes équipables
typedef enum {WARRIOR,RANGER,MAGE,THIEF}Class; //classe choisie par le personnage
typedef enum {RED, BLUE, GREEN, YELLOW}Color;
typedef struct {
	Type type; //nature de la case
	int state; //0 si case cachée, 1 sinon
	int player; //0 si personne 1 , 2 , 3 , 4 en fonct° du joueur
	Coordinates position; //coordonnées de la tuile
}Tile;



typedef struct {
	Weapon weapon; //arme choisie
	Class class; //classe du personnage
	int artifact;//0 si arme antique pas trouvée, 1 sinon
	int chest;//nombre de coffres récupérés: 0, 1 ou 2
	Coordinates position;//position du personnage
	Coordinates spawn; //coordonées du spawn
	Color color; //couleur du perso + spawn
	Coordinates* tiles; //tableau des coordonnées de toutes les tuiles retournées par le joueur en un tour
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
			map[0][i].position.x=0;
			map[0][i].position.y=i;
	}
	for (i=0; i<7; i++){
			map[6][i].state=1;
			map[6][i].type=VOID;
			map[6][i].position.x=6;
			map[6][i].position.y=i;
	}
	for (i=0; i<7; i++){
			map[i][0].state=1;
			map[i][0].type=VOID;
			map[i][0].position.x=i;
			map[i][0].position.y=0;
	}
	for (i=0; i<7; i++){
			map[i][6].state=1;
			map[i][6].type=VOID;
			map[i][6].position.x=i;
			map[i][6].position.y=6;
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
			map[i][k].position.x=i;
			map[i][k].position.y=k;
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

Character chooseWeapon(Character p){  //choix d'une arme à chaque tuile
		int check=0;
		char weapon;
		do{
			printf("Choose a weapon to defend yourself in the next room:\n[1]Torch\n[2]Shield\n[3]Axe\n[4]Bow\n"); //demande tant que réponse incorrecte
			check=scan(&weapon);
		}while(weapon!='1' && weapon!='2' && weapon!='3' && weapon!='4' || check==0);
		switch(weapon){
			case '1':
				printf("\nYou chose a torch to light the way.\n"); //renvoie la valeur correspondant à l'arme dans l'enumération Weapon
				p.weapon=TORCH;
			break;
			case '2':
				printf("\nYou chose a shield to defend yourself.\n");
				p.weapon=SHIELD;
			break;
			case '3':
				printf("\nYou chose an axe to cut down monsters.\n");
				p.weapon=AXE;
			break;
			case '4':
				printf("\nYou chose a bow to kill monsters from afar.\n");
				p.weapon=BOW;
			break;
			default:
				printf("\nErreur 2\n");
				exit(2);
			break;	
		}
		return p;
}

int fightMonster(Character p, Tile monster){
		if (monster.state==1 || monster.type==0 || monster.type>4){
				printf("\nErreur 3\n");
				exit(3); //si tuile déjà explorée ou pas un monstre
		}
		monster.state=1;//on retourne la tuile
		if (p.weapon==NOTHING){
			printf("You don't have a weapon ready.\n");//on vérifie que le joueur a sélectioné une arme
			p=chooseWeapon(p);
		}
		printf("\nA foe attacks you.");
		switch (monster.type){
			case 1:  //en fonction du monstre rencontré, vérifie si le joueur a choisi l'arme appropriée : si oui, renvoie 1, continue; sinon, renvoie 0, respawn.
				printf("\nYou encounter a basilic."); 
				if (p.weapon==SHIELD){
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
				if (p.weapon==AXE){
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
				if (p.weapon==TORCH){
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
				if (p.weapon==BOW){
					printf("\nYou fire an arrow at the harpy from afar with your bow and successfully defat your foe. Victorious, you move onwards.\n");
					return 1;
				}
				else{
					printf("\nYou fail to defeat the monster and die. Restart at the beginning and end your turn here.\n");
					return 0;
				}
			default:
				printf("\nErreur 20\n");
				exit(20);
			break;

		}
}

int legendaryWeapon(Character p, Tile treasure){
	if (treasure.state==1 || treasure.type<7 || treasure.type==11){
		printf("\nErreur 6\n");
		exit(6); //si tuile déjà explorée ou vide ou pas une arme antique
	}
	treasure.state=1;//On retourne la tuile
	printf("\nYou discover an artifact.");
	switch(treasure.type){
		case 7: //épée découverte
			printf("\nYou find the legendary sword of fire.");
			if(p.class==WARRIOR){
				printf("\nAs a warrior, you were looking for this artifact. You take it with you.");
				p.artifact++;
			}
			else{
				printf("\nYou aren't a warrior. Not interested, you leave it there.");
				treasure.state=0;
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
				treasure.state=0;
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
				treasure.state=0;
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
				treasure.state=0;
			}
		break;
		default:
			printf("\nErreur 7\n");
			exit(7);
		break;
	}
	printf("\nYou move on.\n");
	return 1;
}

int totemFunction(Tile totem, Tile map[][ARRAY]){
	if (totem.state==1 || totem.type==0 || totem.type!=TOTEM){
		printf("\nErreur 4\n");
		exit(4); //si tuile déjà explorée ou vide ou pas un totem
	}
	char x;
	char y;
	int a=0;
	int b=0;
	int line, column;
	printf("\nYou find a magical totem glowing ominously. As you feel yourself dying, you are presented with a choice:\n");
	int error=0;
	do{
		do{
			error=0;
			a=0;
			b=0;
			printf("Choose a tile to exchange the totem with (Line and column numbers):\n");
			a=scan(&x);
			b=scan(&y);
			if (a==0 ||b==0){
				error=1;
				printf("\nWrong input!\n");
			}
			if (x>'5' || x<='0' || y>'5' ||y<='0'){
				error=1;
				printf("\nTiles outside the map can not be chosen.\n");
			}	
		}while(error);
		error=0;
		line=x-'0';
		column=y-'0';
		if(map[line][column].state==1){
			error=1;
			printf("\nOnly hidden tiles can be chosen!\n");
		}
		if(map[line-1][column].type==SPAWN || map[line][column-1].type==SPAWN||  map[line+1][column].type==SPAWN || map[line][column+1].type==SPAWN){
			error=1;
			printf("\nTiles directly adjacent to the spawns cannot be selected!\n");
		}
	}while(error);

	Tile tile;
	tile=map[line][column];
	map[line][column].type=TOTEM;
	totem.type=tile.type;
	return 0;
}

int portalFunction(Tile portal, Tile map[][ARRAY], Character p){
	if (portal.state==1 || portal.type==0 || portal.type!=PORTAL){
		printf("\nErreur 14\n");
		exit(14); //si tuile déjà explorée ou vide ou pas un portail
	}
	portal.state=1;//On retourne la tuile
	char x;
	char y;
	int line, column;
	int error=0;
	int a=0;
	int b=0;
	printf("\nYou find a magical portal. As you feel yourself pulled in, you are presented with a choice:\n");
	do{
		do{	
			error=0;
			a=0;
			b=0;
			printf("Choose a tile to be teleported to (Line and column numbers):\n");
			a=scan(&x);
			b=scan(&y);
		
			if (a==0 || b==0){
				error=1;
				printf("\nWrong input!\n");
			}
			if (x>'5' || x<='0' || y>'5' ||y<='0'){
				error=1;
				printf("\nTiles outside the map can not be chosen.\n");
			}	
		}while(error);
			error=0;
			line=x-'0';
			column=y-'0';
		
			if(map[line][column].state==1){
				error=1;
				printf("\nOnly hidden tiles can be chosen!\n");
			}
			if(map[line][column].position.x==portal.position.x && map[line][column].position.y==portal.position.y){
				error=1;
				printf("\nYou cannot choose your current position!\n");
			}
	}while(error);	

	p.position.x=line;
	p.position.y=column;
	return 1;
}
             //tuile retournée, joueur actif, plateau, nombre d'actions du tour (de tuiles retournées)
int revealTile(Tile tile, Character p, Tile map[][ARRAY], int i){ //renvoie 0 si fin du tour, 1 sinon
	if (tile.state==1 || tile.type==0 || tile.type==12){
		printf("\nErreur 24\n");
		exit(24); //si tuile déjà explorée ou vide
	}
	p=chooseWeapon(p); //On choisit une arme
	printf("\nYou enter a new room.");
	p.tiles[i]=tile.position;
	if (tile.type>0 && tile.type<5){
		return fightMonster(p, tile); //si tuile=monstre ->appelle fonction fightMonster, renvoie 0 ou 1 si défaite ou victoire
	}
	else if(tile.type>6 && tile.type<11){
		//si tuile=arme antique->appelle fonction legendaryWeapon, renvoie toujours 1, met à jour le profil du personnage du joueur
		return legendaryWeapon(p, tile);  
	}
	switch(tile.type){
		case 5: //totem découvert
			return totemFunction(tile, map); //à finir
		break;
		case 6://coffre découvert
			tile.state=1;//On retourne la tuile.
			printf("\nYou discover a treasure chest. You loot it and move on.\n");
			p.chest++;
			return 1;
		break;
		case 11: //portail découvert
			return portalFunction(tile, map , p);
		break;
		default:
			printf("\nErreur 5!\n");
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
	int error=0;
	int k=0;
	int a=0;
	char* class;
	char* color;
	for(i=0; i<4; i++){	
		players[i].artifact=0;
		players[i].chest=0;
		players[i].weapon=NOTHING;
		players[i].tiles=malloc(25*sizeof(Coordinates));
		if(players[i].tiles==NULL){
			exit(10);
		}
		for (k=0; k<25; k++){
			players[i].tiles[k].x=0;
			players[i].tiles[k].y=0;
		}
	}
	class=malloc(4*sizeof(char));
	color=malloc(4*sizeof(char));
	if(class==NULL){
		exit(10);
	}
	if(color==NULL){
		exit(10);
	}
	
	for(i=0; i<4; i++){
		
		do{	 
			k=0;
			a=0;
			error=0;
			printf("\nPlayer n°%d:\n",i+1);
			printf("Choose a class for your character:\n[1]Warrior\n[2]Ranger\n[3]Mage\n[4]Thief\n");
			while (a==0){
				a=scan( &class[i]);
			}

			if (class[i]!='1' && class[i]!='2' && class[i]!='3' && class[i]!='4'){
				error=1;
				printf("\nWrong input!\n");
			}
				
			for (k=0;k<i;k++){
				if(class[k]==class[i]){
					error=1;
					printf("\nAlready taken!\n");
				}
			}
		}while(error);//demande tant que réponse incorrecte ou égale aux joueurs précédents
		switch(class[i]){
			case '1':
				printf("\nYou chose to play as a warrior.\n"); 
				players[i].class=0;
			break;
			case '2':
				printf("\nYou chose to play as a ranger.\n");
				players[i].class=1;
			break;
			case '3':
				printf("\nYou chose to play as a mage.\n");
				players[i].class=2;
			break;
			case '4':
				printf("\nYou chose to play as a thief.\n");
				players[i].class=3;
			break;
			default:
				exit(2);
			break;
		}
	}
	for(i=0; i<4; i++){
		 //demande tant que réponse incorrecte
		do{	
			a=0;
			k=0;
			error=0;
			printf("\nPlayer n°%d:\n",i+1);
			printf("Choose a color for your character:\n[1]Red\n[2]Blue\n[3]Green\n[4]Yellow\n");
			while (a==0){
				a=scan( &color[i]);
			}
			if (color[i]!='1' && color[i]!='2' && color[i]!='3' && color[i]!='4'){
				error=1;
				printf("\nWrong input!");
			}
			for (k=0;k<i;k++){
				if(color[k]==color[i]){
					error=1;
					printf("\nAlready taken!");
				}
			}
		}while(error);
		switch(color[i]){		
			case '1': //rouge
				players[i].color=0;
				players[i].position.x=2;
				players[i].spawn.x=2;
				players[i].position.y=0;
				players[i].spawn.y=0;
				
			break;
			case '2': //bleu
				players[i].color=1;
				players[i].position.x=0;
				players[i].spawn.x=0;
				players[i].position.y=4;
				players[i].spawn.y=4;
			break;
			case '3': //vert
				players[i].color=2;
				players[i].position.x=6;
				players[i].spawn.x=6;
				players[i].position.y=2;
				players[i].spawn.y=2;
			break;
			case '4': //jaune
				players[i].color=3;
				players[i].position.x=4;
				players[i].spawn.x=4;
				players[i].position.y=6;
				players[i].spawn.y=6;
			break;
			default: 
				exit(2);
			break;
		}
	}	
	return players;
}

void viewCharacter(Character player,int i){
	switch(player.color){
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
	switch(player.class){
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
	if (player.artifact){
		printf("\nArtifact found.");
	}
	else{
		printf("\nArtifact not found.");
	}
	printf("\nNumber of chests found : %d.",player.chest); 
	printf("\033[00m");
	printf("\n");
	
}


void move(Character p, Tile map[][ARRAY],int i){ // Procédure pour les déplacements d'un joueur
	int x, y, check = 0;
	char m;
	x=p.position.x;
	y=p.position.y;
	do{
		printf("Now choose your way\n\t  Up\n\t  [z]\nLeft [q]        [d] Right\n\t  [s]\n\t Down\n"); //demande tant que réponse incorrecte
		check = scan(&m);
	}while(m != 122  && m != 113 && m != 115 && m != 100 && check != 1);
	switch(m){ // Action à faire selon la direction
		case 'z': // up		
			if((y+1)< 6 && x > 0 && x < 6 && map[x][y+1].state == 0){ // vérifier si la case où on veut aller n'est pas déjà revélée et qu'on se sort pas de la map
				switch (revealTile(map[x][y+1],p,map,i)){
					case '1' : 
						p.position.y = (p.position.y) + 1;
						map[x][y+1].state = 1;
					
					break ;
				
					case '0' : 
						p.position.y = p.spawn.y; // remet les coordonnées du joueur aux valeurs du spawn 
						p.position.x = p.spawn.x;
					
					break ; 

					default :
						printf("\nErreur rencontrée\n");
					break ;
				}
			}	
			else{
				printf("\nYou can't go outside the map \n Please try again \n --------------------------- \n"); // Relance la procédure de déplacement si le joueur tente un déplacement impossible
				move(p,map,i); 
			}	
		break;
		case 'd': //right
			if(x+1 < 6 && y < 6 && y > 0 && map[x+1][y].state == 0){
				switch (revealTile(map[x+1][y],p,map,i)){
					case '1' : 
						p.position.x = (p.position.x) + 1;
						map[x+1][y].state = 1;
					
					break ;
				
					case '0' : 
						p.position.y = p.spawn.y;
						p.position.x = p.spawn.x;
					
					break ; 

					default :
						printf("\nErreur rencontrée\n");
					break ;
				}
			}
			else{
				printf("\nYou can't go on this way Please try again \n --------------------------- \n");
				move(p, map,i);
			}
		break;
		case 'q': //left
			if(x-1 > 0 && y < 6 && y > 0 && map[x-1][y].state == 0){
				switch (revealTile(map[x-1][y],p,map,i)){
					case '1' : 
						p.position.x = (p.position.x) - 1;
						map[x-1][y].state = 1;
					break ;
				
					case '0' : 
						p.position.y = p.spawn.y;
						p.position.x = p.spawn.x;
					
					break ; 

					default :
						printf("\nErreur rencontrée\n");
					break ;
				}
			
			}
			else{
				printf("\nYou can't go on this way Please try again \n --------------------------- \n");
				move(p, map,i);
			}
			break;
		case 's': //down
			if(y-1 > 0 && x < 6 && x > 0 && map[x][y-1].state == 0){
				switch (revealTile(map[x][y-1],p,map,i)){
					case '1' : 
						p.position.y = (p.position.y) - 1;
						map[x][y-1].state = 1;
					break ;
					
					case '0' : 
						p.position.y = p.spawn.y;
						p.position.x = p.spawn.x;
				
					break ; 

					default :
						printf("\nErreur rencontrée\n");
					break ;
				}
			}
			else{
				printf("\nYou can't go on this way Please try again \n --------------------------- \n");
				move(p, map,i);
			}
		break;
		default :	
			exit(2);
		break;
	}
}

int victory(Character p,int i){
	viewCharacter(p,i);
	if (p.chest>0 && p.artifact==1){
		printf("\nYou have successfully found the artifact you were looking for and some loot.\n You have completed your task and leave the dungeon victorious.\n Congratulations ! You have won!\n");
		return 1;
	}
	else{
		printf("\nYou died before finding what you were looking for. You find yourself back at the entrance of the dungeon.\n");
		return 0;
	}
}
int playerTurn(Tile map[][ARRAY], Character p, int i){//tour d'un joueur
	if(map==NULL){
		exit(30);
	}
	printf("\nPlayer n°%d is currently playing:\n",i+1);
	int k=0;
	int win=0;
	printf("\nYou start a new expedition inside the dungeon.\n");
	do{
		move(p,map,k);//déplacement+revealTiles -> retour au spawn inclus dans la fonction
		win=victory(p,i);//vérifie si conditions de victoire résolues
		k++;
	}while(p.position.x!=p.spawn.x && p.position.y!=p.spawn.y || win==0);//fin de boucle = fin du tour
	//réinitialisation de la map
	for (k=0;k<25;k++){
		if(p.tiles[k].x==0 && p.tiles[k].y==0){
		}
		else if (map[p.tiles[k].x][p.tiles[k].y].state==1){
			map[p.tiles[k].x][p.tiles[k].y].state=0;
		}
	}
	//réinitialisation des données du personnage
	p.artifact=0; //armes récupérées 
	p.chest=0; //coffres
	p.weapon=NOTHING; //arme équipée
	if(p.tiles==NULL){
			exit(10);
	}
	for (k=0;k<25;k++){
		p.tiles[k].x=0; //tuiles explorées
		p.tiles[k].y=0;
	}
	return win;	
}

void playGame(){//gestion d'une partie
	Tile map[ARRAY][ARRAY];//genération de la map
 	generateTiles(map);//tab de 7*7 cases
 	viewTiles(map);
 	Character* players; 
 	players=malloc(4*sizeof(Character)); //génération des persos
	if(players==NULL){
		exit(10);
	}
	players=createCharacters();
	int i=0;
	for(i=0;i<4;i++){
		viewCharacter(players[i],i);
	}
	i=0;
	while(playerTurn(map,players[i],i)==0){
		i++;
		if(i>=4){
			i=0;
		}
	}
	printf("\nPlayer n°%d won the game!\n",i+1);
	viewTiles(map);
}

int main (){
 	playGame();
 	return 0;	
 
}
