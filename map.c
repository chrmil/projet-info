
//gestion de la map (pas affichage)			
#include "library.h"

int countTiles(int a, int* compteur){	//gère le compteur et renvoie 0 si le nombre max de cases d'un certain type est déjà atteint et 1 sinon
  switch(a){
	case 1:			//monstres
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
	compteur=malloc(8*sizeof(int));		//compte le nombre de : 0=monstres, 1=totems, 2=coffres, 3=épée, 4=baton, 5=grimoire, 6=dague, 7=portail
	if(compteur==NULL){
		exit(1);
	} 
	for (i=0; i<7; i++){
		map[0][i].state=1;	//contour du plateau, cases vides=cases révélées
		map[0][i].type=VOID;
		map[0][i].position.x=0;
		map[0][i].position.y=i;
		map[0][i].looted=0;
	}
	for (i=0; i<7; i++){
		map[6][i].state=1;
		map[6][i].type=VOID;
		map[6][i].position.x=6;
		map[6][i].position.y=i;
		map[6][i].looted=0;
	}
	for (i=0; i<7; i++){
		map[i][0].state=1;
		map[i][0].type=VOID;
		map[i][0].position.x=i;
		map[i][0].position.y=0;
		map[i][0].looted=0;
	}
	for (i=0; i<7; i++){
		map[i][6].state=1;
		map[i][6].type=VOID;
		map[i][6].position.x=i;
		map[i][6].position.y=6;
		map[i][6].looted=0;
	}
	map[0][4].type=SPAWN;
	map[2][0].type=SPAWN;
	map[4][6].type=SPAWN;
	map[6][2].type=SPAWN;
	int a;
	for (i=1; i<6; i++){
		for(k=1;k<6;k++){
			map[i][k].state=0;	//cases face cachée
			a=rand()%11+1;
			map[i][k].type=a;	//type de la case
			map[i][k].looted=0;
			map[i][k].position.x=i;
			map[i][k].position.y=k;
			//compte le nb de cases d'un type sur le plateau; vérifie qu'il y en ait le bon nb ;
			while(countTiles(a,compteur)==0) {
				a=rand()%11+1;
				map[i][k].type=a;
        		}
    		}
  	}

	printf("\n");
}

void viewTiles(Tile map[][ARRAY]){
	int i,k,j;
	printf("\n");
	for (i=0; i<7; i++){
		printf("\n");
		for(k=0;k<7;k++){
			printf(" %d (%d)",map[i][k].type, map[i][k].state);	//affiche "nature de la case(statut de la case)" pour toute la map + les bords
		}
	}
	printf("\n");
}
void displayAvatarCase(Tile map[][ARRAY],Character* players){ 
int i=0;
	printf("⬛⬛\n⬛⬛");   // si non révélées 
	printf("🔲🔲\n🔲🔲"); // si révélée
	if(tile.player == 1){
		switch(p.class[i]){			// 🧙	 🛡️	🥷	🏹  avatars des persos
			case '1' : // warrior
				printf("🛡️");
			break;
			case '2' : //ranger
				printf(" 🏹 ");
			break;
			case '3' : // mage
				printf("🧙");
			break;
			case'4' :   // thief
				printf("🥷");
			break;
			default : 
				exit(40);
			break;
		} 
	}
//si looted -> changer la place du perso
}
