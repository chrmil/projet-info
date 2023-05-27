//gestion des personnages

#include "library.h"

void createCharacters(Character* players, int nbp){ //création de nbp persos
	if(players==NULL){
		exit(10);
	}
	int i;
	int error=0;
	int k=0;
	int a=0;
	int n=0;
	char alea='0';
	int check=0;
	do{ //création manuelle ou automatique des persos
		printf("\nCreate characters manually ? \n[1]Yes\n[0]No\n");
		check=scan(&alea);
	}while (check==0 || alea!='1' && alea!='0');
	char* class; //stock les classes des persos déjà utilisées
	char* color; //stock les couleurs des persos déjà utilisées
	class=malloc(nbp*sizeof(char));
	color=malloc(nbp*sizeof(char));
	if(class==NULL){
		exit(10);
	}
	if(color==NULL){
		exit(10);
	}
	for(i=0; i<nbp; i++){	//initialise à 0 les différentes variables de la struct Character pour tous les persos
		players[i].artifact=0; 
		players[i].chest=0;
		players[i].weapon=NOTHING;
		players[i].treasure=0;
		players[i].exploration=0;
		players[i].monsters=0;
		players[i].tiles=malloc(25*sizeof(Coordinates)); //créer le tab qui stock les positions des cases explorées pendant 1 tour
		if(players[i].tiles==NULL){
			exit(10);
		}
		for (k=0; k<25; k++){
			players[i].tiles[k].x=0;
			players[i].tiles[k].y=0;
		}
	}
	if(alea=='1'){ //création manuelle des persos
		for(i=0; i<nbp; i++){//génération couleur + class des joueurs
			do{	 //choix de la classe
				k=0;
				a=0;
				error=0;
				printf("\nPlayer n°%d (%s):\n",i+1, players[i].name);
				printf("Choose a class for your character:\n[1]🛡️  Warrior\n[2]🏹 Ranger\n[3]🧙 Mage\n[4]🥷 Thief\n");
				while (a==0){
					a=scan( &class[i]); //check retour de scan
				}
				if (class[i]!='1' && class[i]!='2' && class[i]!='3' && class[i]!='4'){
					error=1; //vérifie que la valeur saisie est 1,2,3 ou 4
					printf("\nWrong input!\n");
				}
				for (k=0;k<i;k++){
					if(class[k]==class[i]){ //vérifie que la classe n'est pas déjà choisie
						error=1;
						printf("\nAlready taken!\n");
					}
				}
			}while(error);//demande tant que réponse incorrecte ou égale aux joueurs précédents
			switch(class[i]){  //séléctionne la classe
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
		for(i=0; i<nbp; i++){
			//demande tant que réponse incorrecte
			do{	//choix de la couleur 
				a=0;
				k=0;
				error=0;
				printf("\nPlayer n°%d (%s):\n",i+1, players[i].name);
				printf("Choose a color for your character:\n\033[01;31m[1]Red\n\033[01;34m[2]Blue\n\033[01;32m[3]Green\n\033[01;33m[4]Yellow\033[00m\n");
				while (a==0){
					a=scan( &color[i]); //check retour de scan
				}
				if (color[i]!='1' && color[i]!='2' && color[i]!='3' && color[i]!='4'){
					error=1; //vérifie que valeur est 1,2,3 ou 4
					printf("\nWrong input!");
				}
				for (k=0;k<i;k++){
					if(color[k]==color[i]){ //vérifie que couleur n'est pas déjà choisie
						error=1;
						printf("\nAlready taken!");
					}
				}
			}while(error);
			switch(color[i]){//séléctionne la couleur, initialise le spawn + la position initiale des joueurs
				case '1':	//rouge
					players[i].color=0;
					players[i].position.x=2;
					players[i].spawn.x=2;
					players[i].position.y=0;
					players[i].spawn.y=0;
				break;
				case '2':	//bleu
					players[i].color=1;
					players[i].position.x=0;
					players[i].spawn.x=0;
					players[i].position.y=4;
					players[i].spawn.y=4;
				break;
				case '3':	//vert
					players[i].color=2;
					players[i].position.x=6;
					players[i].spawn.x=6;
					players[i].position.y=2;
					players[i].spawn.y=2;
				break;
				case '4':	//jaune
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
	}
	else{ //génération couleur + classe des joueurs automatique
		for(i=0; i<nbp; i++){		
			n=0;
			do{ //génération couleur
				error = 0;
				color[i]='1'+n; //dans l'ordre d'énumération
				if (color[i]!='1' && color[i]!='2' && color[i]!='3' && color[i]!='4'){
					error=1; //vérifie la valeur
				}
				for (k=0;k<i;k++){ //vérifie que la couleur est libre
					if(color[k]==color[i]){
						error=1;
					}
				}
				n++;
			}while (error);	
			switch(color[i]){//séléctionne la couleur, initialise le spawn + la position initiale des joueurs	
				case '1':	//rouge
					players[i].color=0;
					players[i].position.x=2;
					players[i].spawn.x=2;
					players[i].position.y=0;
					players[i].spawn.y=0;

				break;
				case '2':	//bleu
					players[i].color=1;
					players[i].position.x=0;
					players[i].spawn.x=0;
					players[i].position.y=4;
					players[i].spawn.y=4;
				break;
				case '3':	//vert
					players[i].color=2;
					players[i].position.x=6;
					players[i].spawn.x=6;
					players[i].position.y=2;
					players[i].spawn.y=2;
				break;
				case '4':	//jaune
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
		for(i=0; i<nbp; i++){ //génération de la classe
			n=0;
			do{
				error = 0;
				class[i]='1'+n; //dans l'ordre d'énumération
				if (class[i]!='1' && class[i]!='2' && class[i]!='3' && class[i]!='4'){
					error=1;  //vérifie la valeur
				}
				for (k=0;k<i;k++){
					if(class[k]==class[i]){//vérifie que la classe est libre
						error=1;
					}
				}
				n++;
			}while (error);		
			switch(class[i]){ //séléctionne la classe
				case '1':
					printf("\nPlayer n°%d : %s will play as a warrior.\n",i+1, players[i].name); 
					players[i].class=0;
				break;
				case '2':
					printf("\nPlayer n°%d : %s will play as a ranger.\n",i+1, players[i].name);
					players[i].class=1;
				break;
				case '3':
					printf("\nPlayer n°%d : %s will play as a mage.\n",i+1, players[i].name);
					players[i].class=2;
				break;
				case '4':
					printf("\nPlayer n°%d : %s will play as a thief.\n",i+1, players[i].name);
					players[i].class=3;
				break;
				default:
					exit(2);
				break;
			}
		}
	}
	free(class);
	free(color); //supprime les tableaux inutiles
	printf("\033[00m");
}

void viewCharacter(Character player,int i){ //affiche les stats d'un joueur
	switch(player.color){ //couleur de l'affichage
		case 0:
			printf("\033[01;31m");		// rouge
		break;
		case 1:
			printf("\033[01;34m");		// bleu
		break;
		case 2:
			printf("\033[01;32m");		// vert
		break;
		case 3:
			printf("\033[01;33m");		// jaune
		break;
		}
	printf("\nPlayer n°%d: %s\n", i+1, player.name); //nom + numéro
	printf("Class: ");
	switch(player.class){ //classe
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
	if (player.artifact){ //arme légendaire récupérée
		printf("\nArtifact found.");
	}
	else{ //arme légendaire pas récupérée
		printf("\nArtifact not found.");
	} //Nombres de coffres, total des trésors trouvés, tuiles explorées, monstres tués au cours de la partie
	printf("\nNumber of chests found : %d.",player.chest); 
	printf("\nScore:");
	printf("\nNumber of treasures found : %d.",player.treasure); 
	printf("\nNumber of tiles explored :  %d.",player.exploration); 
	printf("\nNumber of monsters killed : %d.",player.monsters);
	printf("\033[00m");
	printf("\n");
}
