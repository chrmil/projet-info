
//gestion de la map (pas affichage)			
#include "library.h"

int countTiles(int a, int* compteur){	// gère le compteur et renvoie 0 si le nombre max de cases d'un certain type est déjà atteint et 1 sinon
  switch(a){
	case 1:			// monsters (16)
	case 2:
	case 3:
	case 4:
		if(compteur[0]>=16){
			return 0;
		}
		compteur[0]++;
		return 1;
	break;
	case 5:			// totem (2)
		if (compteur[1]<2){
			compteur[1]++;
			return 1;
		}
		return 0;
	break;
	case 6:			// treasure (2)
		if (compteur[2]<2){
			compteur[2]++;
			return 1;
		}
		return 0;
	break;
	case 7:			// artifact (1 each)
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
	case 11:		// portal (1)
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



void generateTiles(Tile map[][ARRAY]){		// génération du plateau de jeu
	srand( time( NULL ) );
	if (map==NULL){
		exit(1);
	}
	int i,k,j;
	int* compteur=NULL;
	compteur=calloc(8,sizeof(int));		// compte le nombre de : 0=monstres, 1=totems, 2=coffres, 3=épée, 4=baton, 5=grimoire, 6=dague, 7=portail
	if(compteur==NULL){
		exit(1);
	} 
	for (i=0; i<7; i++){
		map[0][i].state=1;		// création des contours du plateau, cases vides=cases révélées
		map[0][i].type=VOID;
		map[0][i].position.x=0;
		map[0][i].position.y=i;
		map[0][i].looted=0;
		map[0][i].player=0;
	}
	for (i=0; i<7; i++){
		map[6][i].state=1;
		map[6][i].type=VOID;
		map[6][i].position.x=6;
		map[6][i].position.y=i;
		map[6][i].looted=0;
		map[6][i].player=0;
	}
	for (i=0; i<7; i++){
		map[i][0].state=1;
		map[i][0].type=VOID;
		map[i][0].position.x=i;
		map[i][0].position.y=0;
		map[i][0].looted=0;
		map[i][0].player=0;
	}
	for (i=0; i<7; i++){
		map[i][6].state=1;
		map[i][6].type=VOID;
		map[i][6].position.x=i;
		map[i][6].position.y=6;
		map[i][6].looted=0;
		map[i][6].player=0;
	} //création des spawns
	map[0][4].type=SPAWN;	//BLEU
	map[2][0].type=SPAWN;	//ROUGE
	map[4][6].type=SPAWN;	//JAUNE
	map[6][2].type=SPAWN;	//VERT
	int a;
	for (i=1; i<6; i++){ //création du plateau joueable
		for(k=1;k<6;k++){
			map[i][k].state=0;	//cases initialememt face cachée
			a=rand()%11+1;
			map[i][k].type=a;	//type de la case déterminés aléatoirement
			map[i][k].looted=0; 	//les cases ne sont pas déjà pillées
			map[i][k].player=0;	//pas de joueurs sur le plateau
			map[i][k].position.x=i; //position de la case stockée
			map[i][k].position.y=k;
			//compte le nb de cases d'un type sur le plateau; vérifie qu'il y en ait le bon nb ;
			while(countTiles(a,compteur)==0) {
				a=rand()%11+1;
				map[i][k].type=a;
			}
		}
	}
	free(compteur); //supprime le compteur, libère de l'espace
	printf("\n");
}

void displayMap(Tile map[][ARRAY],Character p){  //affichage de la map
	int i, k;
//	printf("⬛⬛⬛⬛\n⬛⬛⬛⬛\n⬛⬛⬛⬛");   // si révélées 
//	printf("🔲🔲🔲🔲\n🔲🔲🔲🔲\n🔲🔲🔲🔲"); // si non révélée
	for (i=0; i<7; i++){ //boucle for : gère le n° de ligne
		printf("\n"); //une case = un carré de  4*4 symboles 
		for(k=0;k<7;k++){ //boucle for : gère le n° de colonne; ligne 1/4 de la case
			if(map[i][k].type==SPAWN){ //si case = spawn
				if(i==2 && k==0){//rouge
					printf("🟥🟥🟥🟥 ");
				}
				if(i==6 && k==2){//vert
					printf("🟩🟩🟩🟩 ");
				}
				if(i==0 && k==4){//bleu
					printf("🟦🟦🟦🟦 ");
				}
				if(i==4 && k==6){//jaune
					printf("🟨🟨🟨🟨 ");
				}
			}
			else{ //sinon
				if(map[i][k].state){ //si case révélée
					printf("⬛⬛⬛⬛ ");
				}
				else{ //si case cachée
					printf("🔲🔲🔲🔲 ");
				}
			}
		}
    		printf("\n"); 
		for(k=0;k<7;k++){ //boucle for : gère le n° de colonne; ligne 2/4 de la case
			if(map[i][k].type==SPAWN){ //si case = spawn
				if(i==2 && k==0){//rouge
					printf("🟥🟥🟥🟥 ");
				}
				if(i==6 && k==2){//vert
					printf("🟩🟩🟩🟩 ");
				}
				if(i==0 && k==4){//bleu
					printf("🟦🟦🟦🟦 ");
				}
				if(i==4 && k==6){//jaune
					printf("🟨🟨🟨🟨 ");
				}
			}
			else{
				if(map[i][k].state){ //si case révélée
					printf("⬛⬛⬛⬛ ");
				}
				else{ //si case cachée
					printf("🔲🔲🔲🔲 ");
				}
			}
		}
		printf("\n");	
		for(k=0;k<7;k++){ //boucle for : gère le n° de colonne; ligne 3/4 de la case
			if(map[i][k].state){	//si case révélée
				if(map[i][k].player== 1){ //si joueur présent
          				if (map[i][k].type==SPAWN){ //si case=spawn
		    				if(i==2 && k==0){//rouge
							printf("🟥");
						}
						if(i==6 && k==2){//vert
							printf("🟩");
						}
						if(i==0 && k==4){//bleu
							printf("🟦");
						}
						if(i==4 && k==6){//jaune
							printf("🟨");
						}
						switch(p.class){	// 🧙	 🛡️	🥷	🏹  avatars des persos en fonction de leurs classes
							case 0 : // warrior
								printf("🛡️ ");
							break;
							case 1: //ranger
								printf("🏹 ");
							break;
							case 2 : // mage
								printf("🧙 ");
							break;
							case 3 :   // thief
								printf("🥷 ");
							break;
							default : 
								printf("Error 41");
								exit(40);
							break;
						} 
          				}
          				else{	//si case!=spawn
						switch(p.class){	// 🧙	 🛡️	🥷	🏹  avatars des persos en fonction de leurs classes
							case 0 : // warrior
								printf("⬛🛡️ ");
							break;
							case 1: //ranger
								printf("⬛🏹");
							break;
							case 2 : // mage
								printf("⬛🧙");
							break;
							case 3 :   // thief
								printf("⬛🥷 ");
							break;
							default : 
								printf("Error 40");
								exit(40);
							break;
						} 
					}
         			 //joueur affiché, on affiche le reste de la case
					switch(map[i][k].type){ //en fonction du type
						case 0:
							printf("⬛⬛ ");	
						break;
						case 1:	 //basilic
							printf("🐉⬛ ");
						break;
						case 2: //Troll
							printf("👾⬛ ");
						break;
						case 3: //zombie
							printf("🧟⬛ ");
						break;
						case 4: //harpie
							printf("🪶⬛ ");
						break;
						case 5: //totem
							printf("🔼⬛ ");
						break;
						case 6: //trésor
							printf("💰⬛ ");
						break;
						case 7: //arme = épée
							printf("⚔️⬛ ");
						break;
						case 8: //arme = baton
							printf("🦯⬛ ");
						break;
						case 9: //arme = grimoire
							printf("📜⬛ ");
						break;
						case 10: //arme = dague
							printf("🗡️⬛ ");
						break;
						case 11: //portail
							printf("🛸⬛ ");
						break;
            					case 12 : //spawn
             						 if(i==2 && k==0){//rouge
								printf("🟥🟥 ");
							}
							if(i==6 && k==2){//vert
								printf("🟩🟩 ");
							}
							if(i==0 && k==4){//bleu
								printf("🟦🟦 ");
							}
							if(i==4 && k==6){//jaune
								printf("🟨🟨 ");
							}
           				 	break;
						default: 
                   					printf("Error 1\n");
							exit(1);
						break;
					}
				}
				else if(map[i][k].looted== 1){//si pas de joueur mais case pillée
					printf("⬛⬛⬛⬛ ");
				} 
				else{//si case révélée, non vide et pas de joueur
					switch(map[i][k].type){
						case 0:
							printf("⬛⬛⬛⬛ ");
						break;
						case 1:	
							printf("⬛⬛🐉⬛ ");
						break;
						case 2:
							printf("⬛⬛👾⬛ ");
						break;
						case 3:
							printf("⬛⬛🧟⬛ ");
						break;
						case 4:
							printf("⬛⬛🪶⬛ ");
						break;
						case 5:
							printf("⬛⬛🔼⬛ ");
						break;
						case 6:
							printf("⬛⬛💰⬛ ");
						break;
						case 7:
							printf("⬛⬛⚔️⬛ ");
						break;
						case 8:
							printf("⬛⬛🦯⬛ ");
						break;
						case 9:
							printf("⬛⬛📜⬛ ");
						break;
						case 10:
							printf("⬛⬛🗡️⬛ ");
						break;
						case 11:
							printf("⬛⬛🛸⬛ ");
						break;
						case 12:
							if(i==2 && k==0){//rouge
								printf("🟥🟥🟥🟥 ");
							}
							if(i==6 && k==2){//vert
								printf("🟩🟩🟩🟩 ");
							}
							if(i==0 && k==4){//bleu
								printf("🟦🟦🟦🟦 ");
							}
							if(i==4 && k==6){//jaune
								printf("🟨🟨🟨🟨 ");
							}
						break;
						default: 
              						printf("Error 2");
							exit(1);
						break;
					}
				}
			} 
			else{ //si case cachée
				if(map[i][k].type==SPAWN){ //si spawn
					if(i==2 && k==0){//rouge
						printf("🟥🟥🟥🟥 ");
					}
					if(i==6 && k==2){//vert
						printf("🟩🟩🟩🟩 ");
					}
					if(i==0 && k==4){//bleu
						printf("🟦🟦🟦🟦 ");
					}
					if(i==4 && k==6){//jaune
						printf("🟨🟨🟨🟨 ");
					}
				}
				else{ //sinon
					printf("🔲🔲🔲🔲 ");
				}
			}
		}
		printf("\n");
		for(k=0;k<7;k++){   //boucle for : gère le n° de colonne; ligne 4/4 de la case
			if(map[i][k].type==SPAWN){ //si spawn
				if(i==2 && k==0){//rouge
					printf("🟥🟥🟥🟥 ");
				}
				if(i==6 && k==2){//vert
					printf("🟩🟩🟩🟩 ");
				}
				if(i==0 && k==4){//bleu
					printf("🟦🟦🟦🟦 ");
				}
				if(i==4 && k==6){//jaune
					printf("🟨🟨🟨🟨 ");
				}
			}
			else{
				if(map[i][k].state){//si case révélée
					printf("⬛⬛⬛⬛ ");
				}
				else{//si case cachée
					printf("🔲🔲🔲🔲 ");
				}
			}
		}
		printf("\n");
	}
}
