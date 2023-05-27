//gestion de la partie

#include "library.h"

int stuck(Character* p, Tile map[][ARRAY]){		// checks if the character can move or not (returns 1 if stuck, 0 otherwise)
	int a=0, x, y;
	x=p->position.x;
	y=p->position.y;
	if(map[x+1][y].state == 1 && map[x-1][y].state == 1 && map[x][y+1].state == 1 && map[x][y-1].state == 1){	// if each tile around the player is revealed
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
	if (stuck(p,map)){ //si joueur stuck
		p->position.y = p->spawn.y; //retour au spwan = fin du tour
		p->position.x = p->spawn.x;
	}
	else{ //sinon
		do{
			printf("Now choose your way\n\t  Up\n\t  [z]\nLeft [q]        [d] Right\n\t  [s]\n\t Down\n"); //demande tant que réponse incorrecte
			check = scan(&m);
		}while(m !='z' && m !='q' && m !='s' && m !='d' || check != 1); //vérifie valeur retournée par le scan
		switch(m){ // Action à faire selon la direction
			case 'z': // up		
				if(x-1 > 0 && y < 6 && y > 0 && map[x-1][y].state == 0){ //vérifie que déplacement possible
					p->position.x = (p->position.x) - 1; //déplacement du joueur
					
					switch (revealTile(&map[x-1][y],p,map,i)){ //action -> on retourne la tuile
						case 1:
							map[x-1][y].state = 1; //on continue
						break;
						case 0 : //on retourne au spawn = fin du tour
							map[x-1][y].state = 0;
							p->position.y = p->spawn.y;
							p->position.x = p->spawn.x;
						break ;
						default :
							printf("\nError\n");
						break ;
					}
				}
				else{ //sinon
					printf("\nYou can't go on this way Please try again \n --------------------------- \n");
					move(p, map,i);
				}
			break;
			case 'q': //left
				if(y-1 > 0 && x < 6 && x > 0 && map[x][y-1].state == 0){ //vérifie que déplacement possible
					p->position.y = (p->position.y) - 1;  //déplacement du joueur
					switch (revealTile(&map[x][y-1],p,map,i)){ //action -> on retourne la tuile
						case 1:
							map[x][y-1].state = 1; //on continue
						break;
						case 0 : //on retourne au spawn = fin du tour
							map[x][y-1].state = 0; 
							p->position.y = p->spawn.y;
							p->position.x = p->spawn.x;
						break ; 
						default :
							printf("\nError\n");
						break ;
					}
				}
				else{
					printf("\nYou can't go on this way Please try again \n --------------------------- \n");
					move(p, map,i);
				}
			break;
			case 'd': //right
				if((y+1)< 6 && x > 0 && x < 6 && map[x][y+1].state == 0){// vérifier si la case où on veut aller n'est pas déjà revélée et qu'on ne sort pas de la map
					p->position.y = (p->position.y) + 1; //déplacement du joueur
					switch (revealTile(&map[x][y+1],p,map,i)){ //action -> on retourne la tuile
						case 1:
							map[x][y+1].state = 1;  //on continue
						break;
						case 0 :   //on retourne au spawn = fin du tour
							map[x][y+1].state = 0;
							p->position.y = p->spawn.y;
							p->position.x = p->spawn.x;
						break ;
						default :
							printf("\nError\n");
						break ;
					}
				}	
				else{
					printf("\nYou can't go outside the map \n Please try again \n --------------------------- \n");		// Relance la procédure de déplacement si le joueur tente un déplacement impossible
					move(p,map,i); 
				}	
			break;
			case 's': //down
				if(x+1 < 6 && y < 6 && y > 0 && map[x+1][y].state == 0){ // vérifier si la case où on veut aller n'est pas déjà revélée et qu'on ne sort pas de la map
					p->position.x = (p->position.x) + 1; //déplacement du joueur
					switch (revealTile(&map[x+1][y],p,map,i)){  //action -> on retourne la tuile
						case 1:
							map[x+1][y].state = 1; //on continue
						break;
						case 0 :   //on retourne au spawn = fin du tour
							map[x+1][y].state = 0;
							p->position.y = p->spawn.y;
							p->position.x = p->spawn.x;
						break ; 
						default :
							printf("\nError\n");
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

void firstMove(Character* p, Tile map[][ARRAY],int i){ //déplacement initiale (en début de tour)
	int x, y, check = 0;
	char m;
	x=p->position.x; 
	y=p->position.y;
	if(x==p->spawn.x && y==p->spawn.y){//vérifie que le joueur est au spawn
		switch(p->color){ //selon couleur du joueur (point de spawn)
			case RED: 
				p->position.y = (p->position.y) + 1; //déplacement du joueur
				switch (revealTile(&map[x][y+1],p,map,i)){ //action
					case 1:
						map[x][y+1].state = 1; //on continue
					break;
					case 0 : //on retourne au spawn = fin du tour
						map[x][y+1].state = 0;
						p->position.y = p->spawn.y;
						p->position.x = p->spawn.x;
					break ;
					default :
						printf("\nError\n");
					break ;
				}
			break;
			case BLUE:
				p->position.x = (p->position.x) + 1;  //déplacement du joueur
				switch (revealTile(&map[x+1][y],p,map,i)){ //action
					case 1:
						map[x+1][y].state = 1;//on continue
					break;
					case 0 : //on retourne au spawn = fin du tour
						map[x+1][y].state = 0;
						p->position.y = p->spawn.y;
						p->position.x = p->spawn.x;
					break ; 
					default :
						printf("\nError\n");
					break ;
				}
			break;
			case GREEN:
				p->position.x = (p->position.x) - 1; //déplacement du joueur
				switch (revealTile(&map[x-1][y],p,map,i)){ //action
					case 1:
						map[x-1][y].state = 1; //on continue
					break;
					case 0 :  //on retourne au spawn = fin du tour
						map[x-1][y].state = 0;
						p->position.y = p->spawn.y;
						p->position.x = p->spawn.x;
					break ;
					default :
						printf("\nError\n");
					break ;
				}
			break;
			case YELLOW:
				p->position.y = (p->position.y) - 1; //déplacement du joueur
				switch (revealTile(&map[x][y-1],p,map,i)){ //action
					case 1:
						map[x][y-1].state = 1; //on continue
					break;
					case 0 :  //on retourne au spawn = fin du tour
						map[x][y-1].state = 0;
						p->position.y = p->spawn.y;
						p->position.x = p->spawn.x;
					break ; 
					default :
						printf("\nError\n");
					break ;
				}
			break;
			default:
				exit(21);
			break;
		}
	}
}

int victory(Character* p,int i){ //vérifie si joueur a gagné => 1 si oui, 0 sinon
	viewCharacter(*p,i); //affiche les stats du joueur
	if (p->chest>0 && p->artifact==1){ //vérifie les conditions de victoire
		printf("\nYou have successfully found the artifact you were looking for and some loot.\n You have completed your task and leave the dungeon victorious.\n Congratulations ! You have won!\n");	
		p->win++;
		return 1;
	}
	else{
		return 0;
	}
}

int spawn(Character p){//retourne 1 si joueur au spawn, 0 sinon
	if (p.position.x==p.spawn.x && p.position.y==p.spawn.y){
		return 1;
	}
	else{
		return 0;
	}
}

int playerTurn(Tile map[][ARRAY], Character* p, int i){	//tour d'un joueur
	char c;
	if(map==NULL){
		exit(30);
	}
	printf("\033[2J");
	printf("\033[1;1H");
	map[p->position.x][p->position.y].player=1; //met à jour la position du joueur sur la map
	displayMap(map, *p); //affiche la map
	switch(p->color){ //couleur de l'affichage
		case 0:
			printf("\033[01;31m");
		break;
		case 1:
			printf("\033[01;34m");
		break;
		case 2:
			printf("\033[01;32m");
		break;
		case 3:
			printf("\033[01;33m");
		break;
	}
	printf("\nPlayer n°%d: %s is currently playing\033[00m\n", i+1, p->name); //nom et n° du joueur
	int x=p->position.x;
	int y=p->position.y;
	int k=0;
	int n=0;
	int win=0; 
	printf("\nYou start a new expedition inside the dungeon.\n");
	firstMove(p,map,k); //début du tour -> 1ère action
	win=victory(p,i); //check si joueur a gagné + affiche les stats
	map[x][y].player=0;  //met à jour la position du joueur sur la map
	printf("\nInput anything to continue\n");
	scan(&c);
	printf("\033[2J");
	printf("\033[1;1H");
	k++;
	while(spawn(*p)==0){ //tant que joueur n'est pas sur le spawn => tant que joueur vivant 
		map[p->position.x][p->position.y].player=1;  //met à jour la position du joueur sur la map
		x=p->position.x;
		y=p->position.y;
		move(p,map,k);//déplacement+revealTiles -> retour au spawn inclus dans la fonction
		win=victory(p,i);//vérifie si conditions de victoire résolues + affiche stats
		k++;
		map[x][y].player=0;  //met à jour la position du joueur sur la map
		printf("\nInput anything to continue\n");
		scan(&c);
		printf("\033[2J");
		printf("\033[1;1H");
		if(win){ //victoire => fin du tour
			break;
		}
	}	//fin de boucle = fin du tour
	map[p->position.x][p->position.y].player=0; //met à jour la position du joueur sur la map
	if(win==0){ //si joueur est mort
		printf("\n\033[01;31mYou died before finding what you were looking for. You find yourself back at the entrance of the dungeon.\033[00m\n");
		printf("\nInput anything to end your turn\n");
		scan(&c);
		//réinitialisation de la map
		for (k=0;k<25;k++){
			if(p->tiles[k].x==0 && p->tiles[k].y==0){
			}
			else if (map[p->tiles[k].x][p->tiles[k].y].state==1 || map[p->tiles[k].x][p->tiles[k].y].looted==1){
				map[p->tiles[k].x][p->tiles[k].y].state=0;
				map[p->tiles[k].x][p->tiles[k].y].looted=0;
			}
		}
		//réinitialisation des données du personnage
		p->artifact=0;		//armes récupérées 
		p->chest=0;		//coffres
		p->weapon=NOTHING;	//arme équipée
	}
	else{ //si joueur a gagné
		for (k=0;k<7;k++){
			for (n=0;n<7;n++){
				map[n][k].state=1;
				map[n][k].looted = 0;
			}
		}
		displayMap(map, *p); //affiche la map
	}
	if(p->tiles==NULL){
		exit(10);
	}
	for (k=0;k<25;k++){ //réinitialise le compteur des tuiles explorées
		p->tiles[k].x=0; 
		p->tiles[k].y=0;
	}
	return win;
}

void playGame(char nbp, Character* players){//gestion d'une partie
	char c;
	time_t begin = time( NULL ); //temps de début de la partie
	Tile map[ARRAY][ARRAY];//plateau de 7*7 cases
	generateTiles(map);//genération de la map
	if(players==NULL){
		exit(10);
	}
	createCharacters(players,nbp);//création des persos
	int i=0;
	for(i=0;i<nbp;i++){
		viewCharacter(players[i],i); //affichage des stats des joueurs
	}
	printf("\nInput anything to continue\n");
	scan(&c);
	i=0;
	while(playerTurn(map,&players[i],i)==0){ //tours de chaque joueur tant que pas de gagnant
		i++;
		if(i>=nbp){
			i=0;
		}
	}
	printf("\nPlayer n°%d won the game! 🏆  \n",i+1); //victoire
	time_t end= time( NULL ); //temps de fin de la partie
	unsigned long secondes=difftime( end, begin ); //temps de la partie
	unsigned long minutes=secondes /60;
	secondes=secondes%60;
	unsigned long hours=minutes /60;
	minutes=minutes%60;
  	printf( "Finished in %ld h %ld min %ld sec\n",hours, minutes, secondes ); //affichage chrono en h:min:s
	for(i=0;i<nbp;i++){
		viewCharacter(players[i],i); //affichage des stats des joueurs
	}
	printf("\nInput anything to end the game\n");
	finish(nbp, players); //fin de la partie
}
