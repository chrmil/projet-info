// ------ Système de déplacement -------

#include "library.h"

void viewPosition(Character p){ // Procédure pour voir la position d'un joueur 
	printf("\n %d your position is : X = %d / Y = %d .\n", p.class, p.position.x, p.position.y);
}

void countTilesReveal(Tile map[][ARRAY]){ // Compter les cases déjà révélées
	int i,k, count;
	printf("\n");
	for (i= 1; i<6; i++){
		for(k=1;k<6;k++){
			if(map[i][k].state == 1){		// vérifie état des cases de toute la map et rajoute 1 au compteur si révélée
				count=count++;
			}

		}
	}
	printf("\nThere is/are %d tiles reveal\n", count);
}

/*
void move(Character p, Tile map[][ARRAY],int i){ // Procédure pour les déplacements d'un joueur
	int x, y, a, check = 0;
	char m;
	x=p.position.x;
	y=p.position.y;
	printf("\nx = %d ; y = %d\n", x, y);
	do{
		printf("Now choose your way\n\t  Up\n\t  [z]\nLeft [q]        [d] Right\n\t  [s]\n\t Down\n"); //demande tant que réponse incorrecte
		check = scan(&m);
	}while(m != 'z'  && m != 'q' && m != 's' && m != 'd' && check != 1);
	switch(m){ // Action à faire selon la direction
		case 'z': // up		
			if((y+1)< 6 && x > 0 && x < 6 && map[x][y+1].state == 0){ // vérifier si la case où on veut aller n'est pas déjà revélée et qu'on se sort pas de la map
				a = revealTile(map[x][y+1],p,map,i);
				switch (a){
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
				a = revealTile(map[x][y+1],p,map,i);
				switch (a){
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
				a = revealTile(map[x][y+1],p,map,i);
				switch (a){
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
				a = revealTile(map[x][y+1],p,map,i);
				switch (a){
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
	}
}
*/
// map[0][i].state=1; //contour du plateau, cases vides=cases révélées
