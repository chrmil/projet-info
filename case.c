///generation de la map
 
#include <stdio.h>
#include <math.h>
#include <stdlib.h>  
#include <unistd.h>
#include <time.h>
#include <sys/time.h>
#include <string.h>
#define ARRAY 7


//nature de la case 
typedef enum {VIDE/*0*/ , BASILIC/*1*/, TROLL/*2*/, ZOMBIE/*3*/, HARPIE/*4*/, TOTEM/*5*/, COFFRE/*6*/, EPEE/*7*/, BATON/*8*/, GRIMOIRE/*9*/, DAGUE/*10*/, PORTAIL /*11*/}Type;
typedef enum {TORCHE,BOUCLIER,HACHE,ARC}Arme; //armes équipables

typedef struct {
	Type type; //nature de la case
	int statut; //0 si case cachée, 1 sinon
}Case;

int count(int a, int* compteur){//gère le compteur et renvoie 0 si le nombre max de cases d'un ceratin type est déjà atteint et 1 sinon
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



void generateMap(Case map[][ARRAY]){
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
			map[0][i].statut=1; //contour du plateau, cases vides=cases révélées
			map[0][i].type=VIDE;
	}
	for (i=0; i<7; i++){
			map[6][i].statut=1;
			map[6][i].type=VIDE;
	}
	for (i=0; i<7; i++){
			map[i][0].statut=1;
			map[i][0].type=VIDE;
	}
	for (i=0; i<7; i++){
			map[i][6].statut=1;
			map[i][6].type=VIDE;
	}
	int a;
	for (i=1; i<6; i++){
		for(k=1;k<6;k++){
			map[i][k].statut=0;//cases face cachée
      			a=rand()%11+1;
			map[i][k].type=a; //type de la case
			//compte le nb de cases d'un type sur le plateau; vérifie qu'il y en ait le bon nb ;
	      		while(count(a,compteur)==0) {
              			a=rand()%11+1;
              			map[i][k].type=a;
        		}
    		}
  	}
 	for(i=0;i<8;i++){
     		printf("\nCompteur n°%d est à %d.",i,compteur[i]);
 	}
	printf("\n");
}

void viewMap(Case map[][ARRAY]){
	int i,k,j;
	printf("\n");
	for (i=0; i<7; i++){
	printf("\n");
		for(k=0;k<7;k++){
			printf(" %d (%d)",map[i][k].type, map[i][k].statut);//affiche "nature de la case(statut de la case)" pour toute la map + les bords

		}
	}
	printf("\n");
}

int main (){
 	Case map[ARRAY][ARRAY];
 	generateMap(map);//tab de 7*7 cases
 	viewMap(map);
 	return 0;
}
