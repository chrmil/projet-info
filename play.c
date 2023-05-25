//gestion de la partie

#include "library.h"

int stuck(Character* p, Tile map[][ARRAY]){
	int a=0, x, y;
	x=p->position.x;
	y=p->position.y;
	if(map[x+1][y].state == 1 && map[x-1][y].state == 1 && map[x][y+1].state == 1 && map[x][y-1].state == 1){
		printf("\nYou're stuck. Restart at the beginning and end your turn here.\n");
		a = 1;
	}
	return a;
}

void move(Character* p, Tile map[][ARRAY],int i){ // Procédure pour les déplacements d'un joueur
	int x, y, check = 0;
	char m;
	x=p->position.x;
	y=p->position.y;
	if (stuck(p,map)){
		p->position.y = p->spawn.y;
		p->position.x = p->spawn.x;
	}
	else{
		do{
			printf("Now choose your way\n\t  Up\n\t  [z]\nLeft [q]        [d] Right\n\t  [s]\n\t Down\n"); //demande tant que réponse incorrecte
			check = scan(&m);
		}while(m !='z' && m !='q' && m !='s' && m !='d' || check != 1);
		switch(m){ // Action à faire selon la direction
			case 'z': // up		
				if(x-1 > 0 && y < 6 && y > 0 && map[x-1][y].state == 0){
					switch (revealTile(&map[x-1][y],p,map,i)){
						case 1 : 
							p->position.x = (p->position.x) - 1;
							map[x-1][y].state = 1;
						break ;
						case 0 : 
							p->position.y = p->spawn.y;
							p->position.x = p->spawn.x;
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
				if(y-1 > 0 && x < 6 && x > 0 && map[x][y-1].state == 0){
					switch (revealTile(&map[x][y-1],p,map,i)){
						case 1 : 
							p->position.y = (p->position.y) - 1;
							map[x][y-1].state = 1;
						break ;
						case 0 : 
							p->position.y = p->spawn.y;
							p->position.x = p->spawn.x;
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
			case 'd': //right
				if((y+1)< 6 && x > 0 && x < 6 && map[x][y+1].state == 0){		// vérifier si la case où on veut aller n'est pas déjà revélée et qu'on se sort pas de la map
					switch (revealTile(&map[x][y+1],p,map,i)){
						case 1 : 
							p->position.y = (p->position.y) + 1;
							map[x][y+1].state = 1;
						break ;
						case 0 : 
							p->position.y = p->spawn.y;
							p->position.x = p->spawn.x;
						break ;
						default :
							printf("\nErreur rencontrée\n");
						break ;
					}
				}	
				else{
					printf("\nYou can't go outside the map \n Please try again \n --------------------------- \n");		// Relance la procédure de déplacement si le joueur tente un déplacement impossible
					move(p,map,i); 
				}	
			break;
			case 's': //down
				if(x+1 < 6 && y < 6 && y > 0 && map[x+1][y].state == 0){
					switch (revealTile(&map[x+1][y],p,map,i)){
						case 1 : 
							p->position.x = (p->position.x) + 1;
							map[x+1][y].state = 1;
						break ;
						case 0 : 
							p->position.y = p->spawn.y;
							p->position.x = p->spawn.x;
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
}

void firstMove(Character* p, Tile map[][ARRAY],int i){
	int x, y, check = 0;
	char m;
	x=p->position.x;
	y=p->position.y;
	if(x==p->spawn.x && y==p->spawn.y){//si joueur au spawn
		switch(p->color){
			case RED:
				switch (revealTile(&map[x][y+1],p,map,i)){
					case 1 : 
						p->position.y = (p->position.y) + 1;
						map[x][y+1].state = 1;
					break ;
					case 0 : 
						p->position.y = p->spawn.y; // remet les coordonnées du joueur aux valeurs du spawn 
						p->position.x = p->spawn.x;
					break ; 
					default :
						printf("\nErreur rencontrée\n");
					break ;
				}
			break;
			case BLUE:
				switch (revealTile(&map[x+1][y],p,map,i)){
					case 1 : 
						p->position.x = (p->position.x) + 1;
						map[x+1][y].state = 1;
					break ;
					case 0 : 
						p->position.y = p->spawn.y;
						p->position.x = p->spawn.x;
					break ; 
					default :
						printf("\nErreur rencontrée\n");
					break ;
				}
			break;
			case GREEN:
				switch (revealTile(&map[x-1][y],p,map,i)){
					case 1 : 
						p->position.x = (p->position.x) - 1;
						map[x-1][y].state = 1;
					break ;
					case 0 : 
						p->position.y = p->spawn.y;
						p->position.x = p->spawn.x;
					break ;
					default :
						printf("\nErreur rencontrée\n");
					break ;
				}
			break;
			case YELLOW:
				switch (revealTile(&map[x][y-1],p,map,i)){
					case 1 : 
						p->position.y = (p->position.y) - 1;
						map[x][y-1].state = 1;
					break ;
					case 0 : 
						p->position.y = p->spawn.y;
						p->position.x = p->spawn.x;
					break ; 
					default :
						printf("\nErreur rencontrée\n");
					break;
				}
			break;
			default:
				exit(21);
			break;
		}
	}
}

int victory(Character* p,int i){
	viewCharacter(*p,i);
	if (p->chest>0 && p->artifact==1){
		printf("\nYou have successfully found the artifact you were looking for and some loot.\n You have completed your task and leave the dungeon victorious.\n Congratulations ! You have won!\n");	
		p->win++;
		return 1;
	}
	else{
		return 0;
	}
}

int spawn(Character p){//1 si joueur au spawn, 0 sinon
	if (p.position.x==p.spawn.x && p.position.y==p.spawn.y){
		return 1;
	}
	else{
		return 0;
	}
}

int playerTurn(Tile map[][ARRAY], Character p, int i){//tour d'un joueur
	if(map==NULL){
		exit(30);
	}
	printf("\033[2J");
	printf("\033[1;1H");
	printf("\nPlayer n°%d: %s is currently playing\n", i+1, p.name);
	int k=0;
	int win=0;
	printf("\nYou start a new expedition inside the dungeon.\n");
	firstMove(&p,map,k);
	win=victory(&p,i);
	k++;
	while(spawn(p)==0){
		move(&p,map,k);//déplacement+revealTiles -> retour au spawn inclus dans la fonction
		win=victory(&p,i);//vérifie si conditions de victoire résolues
		k++;
		printf("\033[2J");
		printf("\033[1;1H");
		if(win){
			break;
		}
	}	//fin de boucle = fin du tour
	if(win==0){
		printf("\nYou died before finding what you were looking for. You find yourself back at the entrance of the dungeon.\n");
		//viewTiles(map);
		//réinitialisation de la map
		for (k=0;k<25;k++){
			if(p.tiles[k].x==0 && p.tiles[k].y==0){
			}
			else if (map[p.tiles[k].x][p.tiles[k].y].state==1){
				map[p.tiles[k].x][p.tiles[k].y].state=0;
			}
		}
		//réinitialisation des données du personnage
		p.artifact=0;		//armes récupérées 
		p.chest=0;		//coffres
		p.weapon=NOTHING;	//arme équipée
	}
	else{
		for (k=0;k<25;k++){
			if(p.tiles[k].x==0 && p.tiles[k].y==0){
			}
			else if (map[p.tiles[k].x][p.tiles[k].y].state==0){
				map[p.tiles[k].x][p.tiles[k].y].state=1;
			}
		}
	}
	if(p.tiles==NULL){
		exit(10);
	}
	for (k=0;k<25;k++){
		p.tiles[k].x=0; //tuiles explorées
		p.tiles[k].y=0;
	}
	return win;	
}


void playGame(char nbp, Character* players){//gestion d'une partie
	Tile map[ARRAY][ARRAY];//genération de la map
	generateTiles(map);//tab de 7*7 cases
	//viewTiles(map);
	if(players==NULL){
		exit(10);
	}
	players=createCharacters(players,nbp);
	int i=0;
	for(i=0;i<nbp;i++){
		viewCharacter(players[i],i);
	}
	i=0;
	while(playerTurn(map,players[i],i)==0){
		i++;
		if(i>=nbp){
			i=0;
		}
	}
	printf("\nPlayer n°%d won the game!\n",i+1);
	viewTiles(map);
	finish(nbp, players);
}

