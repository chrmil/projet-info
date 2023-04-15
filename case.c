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

	j=11;
	for (i=1; i<6; i++){
		for(k=1;k<6;k++){
			map[i][k].statut=0;//cases face cachée
			map[i][k].type=rand()%j+1; //type de la case
			//compte le nb de cases d'un type sur le plateau; vérifie qu'il y en ait le bon nb ;
			if (map[i][k].type<5 && map[i][k].type>0){ //monstres
				compteur[0]++; 
				if (compteur[0]>16){
					map[i][k].type=rand()%7+5;
        				compteur[0]--;
				}
			}
			if (map[i][k].type==TOTEM){
				compteur[1]++;
				if (compteur[1]>2){
					map[i][k].type=rand()%4+1;
         				compteur[1]--;
          				compteur[0]++;
				}
				if (compteur[1]==2 && j==5){
					j--;
				}
			}
			if (map[i][k].type==COFFRE){
				compteur[2]++; 
				if (compteur[2]>2){
					map[i][k].type=rand()%4+1;
          				compteur[2]--;
          				compteur[0]++;
				}
				if (compteur[2]==2 && j==6){
					j--;
				}
			}
			if (map[i][k].type==EPEE){
				compteur[3]++; 
				if (compteur[3]>1){
					map[i][k].type=rand()%4+1;
          				compteur[3]--;
          				compteur[0]++;
				}
				if (compteur[3]==1 && j==7){
					j--;
				}
			}
			if (map[i][k].type==BATON){
				compteur[4]++; 
				if (compteur[4]>1){
					map[i][k].type=rand()%4+1;
          				compteur[4]--;
          				compteur[0]++;
				}
				if (compteur[4]==1 && j==8){
					j--;
				}
			}
			if (map[i][k].type==GRIMOIRE){
				compteur[5]++;
				if (compteur[5]>1){
					map[i][k].type=rand()%4+1;
          				compteur[5]--;
          				compteur[0]++;
				}
				if (compteur[5]==1 && j==9){
					j--;
				}
			}
			if (map[i][k].type==DAGUE){
				compteur[6]++;
				if (compteur[6]>1){
					map[i][k].type=rand()%4+1;
          				compteur[6]--;
          				compteur[0]++;
				}
				if (compteur[6]==1 && j==10){
					j--;
				}
			}
			if (map[i][k].type==PORTAIL){
				compteur[7]++;
				j--;

			}
      			if (map[i][k].type==VIDE){
       		 		printf("\nVide=%d %d\n",i,k);
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
			printf(" %d (%d)",map[i][k].type, map[i][k].statut);

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

