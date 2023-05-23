//fonctions de gestion des événements et actions pour un tour
#include "library.h"

void chooseWeapon(Character* p){  //choix d'une arme à chaque tuile
		int check=0;
		char weapon;
		do{
			printf("Choose a weapon to defend yourself in the next room:\n[1]Torch\n[2]Shield\n[3]Axe\n[4]Bow\n"); //demande tant que réponse incorrecte
			check=scan(&weapon);
		}while(weapon!='1' && weapon!='2' && weapon!='3' && weapon!='4' || check==0);
		switch(weapon){
			case '1':
				printf("\nYou chose a torch to light the way.\n"); //renvoie la valeur correspondant à l'arme dans l'enumération Weapon
				p->weapon=TORCH;
			break;
			case '2':
				printf("\nYou chose a shield to defend yourself.\n");
				p->weapon=SHIELD;
			break;
			case '3':
				printf("\nYou chose an axe to cut down monsters.\n");
				p->weapon=AXE;
			break;
			case '4':
				printf("\nYou chose a bow to kill monsters from afar.\n");
				p->weapon=BOW;
			break;
			default:
				printf("\nErreur 2\n");
				exit(2);
			break;	
		}
}

int fightMonster(Character* p, Tile* monster){
		if (monster->state==1 || monster->type==0 || monster->type>4){
				printf("\nErreur 3\n");
				exit(3); //si tuile déjà explorée ou pas un monstre
		}
		monster->state=1;//on retourne la tuile
		if (p->weapon==NOTHING){
			printf("You don't have a weapon ready.\n");//on vérifie que le joueur a sélectioné une arme
			chooseWeapon(p);
		}
		printf("\nA foe attacks you.");
		switch (monster->type){
			case 1:  //en fonction du monstre rencontré, vérifie si le joueur a choisi l'arme appropriée : si oui, renvoie 1, continue; sinon, renvoie 0, respawn.
				printf("\nYou encounter a basilic."); 
				if (p->weapon==SHIELD){
					printf("\nYou reflect the basilic's deadly glare with your shield and successfully defat your foe. Victorious, you move onwards.\n");
					p->monsters++;
					return 1;
				}
				else{
					printf("\nYou fail to defeat the monster and die. Restart at the beginning and end your turn here.\n");
					return 0;
				}
			break;
			case 2:
				printf("\nYou encounter a troll."); 
				if (p->weapon==AXE){
					printf("\nYou cut down the troll with your axe and successfully defat your foe. Victorious, you move onwards.\n");
					p->monsters++;
					return 1;
				}
				else{
					printf("\nYou fail to defeat the monster and die. Restart at the beginning and end your turn here.\n");
					return 0;
				}
			break;
			case 3:
				printf("\nYou encounter a zombie.");
				if (p->weapon==TORCH){
					printf("\nYou set the zombie on fire with your torch and successfully defat your foe. Victorious, you move onwards.\n");
					p->monsters++;
					return 1;
				}
				else{
					printf("\nYou fail to defeat the monster and die. Restart at the beginning and end your turn here.\n");
					return 0;
				}
			break;
			case 4:
				printf("\nYou encounter a harpy.");
				if (p->weapon==BOW){
					printf("\nYou fire an arrow at the harpy from afar with your bow and successfully defat your foe. Victorious, you move onwards.\n");
					p->monsters++;
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

int legendaryWeapon(Character* p, Tile* treasure){
	if (treasure->state==1 || treasure->type<7 || treasure->type>=11){
		printf("\nErreur 6\n");
		exit(6); //si tuile déjà explorée ou vide ou pas une arme antique
	}
	treasure->state=1;//On retourne la tuile
	printf("\nYou discover an artifact.");
	switch(treasure->type){
		case 7: //épée découverte
			printf("\nYou find the legendary sword of fire.");
			if(p->class==WARRIOR){
				printf("\nAs a warrior, you were looking for this artifact. You take it with you.");
				p->artifact++;
			}
			else{
				printf("\nYou aren't a warrior. Not interested, you leave it there.");
				treasure->state=0;
			}
		break;
		case 8: //baton découvert
			printf("\nYou find the legendary familiars' command staff.");
			if(p->class==RANGER){
				printf("\nAs a ranger, you were looking for this artifact. You take it with you.");
				p->artifact++;
			}
			else{
				printf("\nYou aren't a ranger. Not interested, you leave it there.");
				treasure->state=0;
			}
		break;
		case 9://grimoire découvert
			printf("\nYou find the legendary spellbook.");
			if(p->class==MAGE){
				printf("\nAs a mage, you were looking for this artifact. You take it with you.");
				p->artifact++;
			}
			else{
				printf("\nYou aren't a mage. Not interested, you leave it there.");
				treasure->state=0;
			}
		break;
		case 10: //dague découverte
			printf("\nYou find the legendary dagger of sleep.");
			if(p->class==THIEF){
				printf("\nAs a thief, you were looking for this artifact. You take it with you.");
				p->artifact++;
			}
			else{
				printf("\nYou aren't a thief. Not interested, you leave it there.");
				treasure->state=0;
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

int totemFunction(Tile* totem, Tile map[][ARRAY]){
	if (totem->state==1 || totem->type==0 || totem->type!=TOTEM){
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
	totem->type=tile.type;
	return 0;
}

int portalFunction(Tile* portal, Tile map[][ARRAY], Character* p, int i){
	if (portal->state==1 || portal->type==0 || portal->type!=PORTAL){
		printf("\nErreur 14\n");
		exit(14); //si tuile déjà explorée ou vide ou pas un portail
	}
	portal->state=1;//On retourne la tuile
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
			if(map[line][column].position.x==portal->position.x && map[line][column].position.y==portal->position.y){
				error=1;
				printf("\nYou cannot choose your current position!\n");
			}
	}while(error);	

	p->position.x=line;
	p->position.y=column;
	return revealTile(&map[line][column],p,map,i+1);
}


             //tuile retournée, joueur actif, plateau, nombre d'actions du tour (de tuiles retournées)
int revealTile(Tile* tile, Character* p, Tile map[][ARRAY], int i){ //renvoie 0 si fin du tour, 1 sinon
	if (tile->state==1 || tile->type==0 || tile->type==12){
		printf("\nErreur 24\n");
		exit(24); //si tuile déjà explorée ou vide
	}
	chooseWeapon(p); //On choisit une arme
	printf("\nYou enter a new room.");
	p->exploration++;
	p->tiles[i]=tile->position;
	if (tile->type>0 && tile->type<5){
		return fightMonster(p, tile); //si tuile=monstre ->appelle fonction fightMonster, renvoie 0 ou 1 si défaite ou victoire
	}
	else if(tile->type>6 && tile->type<11){
		//si tuile=arme antique->appelle fonction legendaryWeapon, renvoie toujours 1, met à jour le profil du personnage du joueur
		p->treasure++;
		return legendaryWeapon(p, tile);  
	}
	switch(tile->type){
		case 5: //totem découvert
			return totemFunction(tile, map); //à finir
		break;
		case 6://coffre découvert
			tile->state=1;//On retourne la tuile.
			printf("\nYou discover a treasure chest. You loot it and move on.\n");
			p->chest++;
			p->treasure++;
			return 1;
		break;
		case 11: //portail découvert
			return portalFunction(tile, map , p,i);
		break;
		default:
			printf("\nErreur 5!\n");
			exit(5);
			
		break;
	}
}
