///exo_3: tris lents//
#include <stdio.h>
#include <math.h>
#include <stdlib.h>  
#include <unistd.h>
#include <time.h>
#include <string.h>
#include <sys/time.h>
#define TAILLE 100

int askUserInt(int min, int max){
	char s[1000];
	printf("\nSaisir un entier entre %d et %d :\n",min,max);
	int b=scanf("%s",&s);
	int a=atoi(s);
	if (a<min || a>max){
		b=0;
	}
	if (b!=1){
		return askUserInt(min,max);
	}
	return a;
}


//fonction pour mesurer temps (en ms)
long getTimeMs(){
	struct timeval tv;
	gettimeofday(&tv,NULL);
	return (tv.tv_sec*1000)+(tv.tv_usec/1000);
}



void printArray(int tab[], int size){
	if (tab==NULL || size<=0){
		exit(20);
	}
	int i;
	printf("\n");
	for (i=0;i<size;i++){
		printf("| %d ",tab[i]);
	}
	printf("|\n");   //fflsuh(stdout) : force les données à ê afficher sur le terminal

}

void fillArray(int tab[], int size){
	if (tab==NULL || size<=0){
		exit(20);
	}
	int i;
	srand( time( NULL ) );
	for (i=0;i<size;i++){
		tab[i]=rand()%1000+1;
	}
}
//1 si tab trié par ordre croissant, 0 sinon
int tabTri(int tab[], int size){
	if (tab==NULL || size<=0){
		exit(20);
	}
	int i;
	for (i=0;i<size-1;i++){
		if (tab[i]>tab[i+1]){
			return 0;
		}
	}
	return 1;
}


//Tri fusion :

//fusion des sous-tabs
void fusion(int tab[], int debut, int milieu, int fin){
	int i,k,j;
	int tab2[TAILLE];
	k=debut;
	j=fin;
	for (i=debut; i<milieu+1;i++){
		tab2[i]=tab[i];
	}
	for (i=milieu+1; i<fin+1;i++){
		tab2[i]=tab[fin-i+milieu+1];
	}
	for (i=debut; i<fin+1; i++){
		if(tab2[k]<=tab2[j]){
			tab[i]=tab2[k];
			k++;
		}
		else{
			tab[i]=tab2[j];
			j--;
		}
	}
		
}
void triFusionRec(int tab[], int debut, int fin){//fonction récursive : tri par fusion
	int milieu;
	if (debut<fin){
		milieu=(debut+fin)/2;   //divise le tab en sous-tabs
		triFusionRec(tab,debut,milieu);
		triFusionRec(tab,milieu+1,fin);
		fusion(tab,debut,milieu,fin); //fusionne tous les sous-tabs dans l'ordre croissant
	}
}

void triFusion(int tab[], int size){ //tri à fusion, met les variables de la fct° récursive à la bonne valeur
	if (tab==NULL || size<=0){
		exit(20);
	}
	if (tabTri(tab,size)){
		return;
	}
	triFusionRec(tab,0,size-1);
}


//tri rapide

//selection du pivot

int partition(int tab[], int debut, int fin){
	int inf,sup,temp;
	inf=debut+1;
	sup=fin;
	while(inf<=sup){ 
		while(tab[inf]<=tab[debut] && inf<fin){
			inf++;
		}
		while(tab[sup]>=tab[debut] && sup>debut){
			sup--;
		}
		
		if (inf<=sup){
			temp=tab[sup];
			tab[sup]=tab[inf];
			tab[inf]=temp;
		}
		if (inf==sup){
			break;
		}
	
	}

	temp=tab[debut];
	tab[debut]=tab[sup];
	tab[sup]=temp;

	return sup;
}

void triRapideRec(int tab[],int debut,int fin){  //fonct° récursive
	int pivot;
	if (debut<fin && debut>=0){
		pivot=partition(tab,debut,fin); //selection du pivot
		triRapideRec(tab,debut,pivot-1);
		triRapideRec(tab,pivot+1,fin);	
	}	
}

void triRapide(int tab[],int size){ //appel à la fonct° récursive, met les variables de la fct° à la bonne valeur
	if (tab==NULL || size<=0){
		exit(20);
	}
	if (tabTri(tab,size)){
		return;
	}
	triRapideRec(tab,0,size-1);
}

/*
void triSelection(int tab[ ], int size){
	size--;
	if (tab==NULL || size<=0){
		exit(20);
	}
	int i,k;  //chercher le min du tab, le passer au début, décaler le début de 1, recommencer
	int min;
	int temp;
	if (tabTri(tab,size)){
		return;
	}
	for (i=0;i<size;i++){
		min=i;
		for(k=i+1;k<=size;k++){
			if (tab[min]>tab[k]){
				min=k;
			}
		}
		if(tab[i]!=tab[min]){
			temp=tab[i];
			tab[i]=tab[min];
			tab[min]=temp;
		}
	}
}

void triBulle(int tab[],int size){
	size--;
	if (tab==NULL || size<=0){
		exit(20);
	}
	if (tabTri(tab,size)){
		return;
	}
	int i,k; //comparer 1 par 1, décaler, recommencer jusqu'à tab trié
	int temp;
	int tri=0;
	k=size;
	do{     
		tri=0;
		for(i=0;i<k;i++){
			if(tab[i]>tab[i+1]){
				temp=tab[i];
				tab[i]=tab[i+1];
				tab[i+1]=temp;
				tri=1;
			}
		}
		k--;
	}while(tri && k>0);
}

void triInsertion(int tab[],int size){
	size--;
	if (tab==NULL || size<=0){
		exit(20);
	}
	if (tabTri(tab,size)){
		return;
	}
	int i,k;
	int temp;
	for(i=1; i<=size;i++){
		temp=tab[i];
		k=i-1;
		while((k>=0) && (tab[k]>temp)){
			tab[k+1]=tab[k];
			k=k-1;
		}
	tab[k+1]=temp;
	}
}

int rechercheTab(int tab[],int size, int val){ //1 si val dans tab, 0 sinon
	if (tab==NULL || size<=0){
		exit(20);
	}
	int i;
	for (i=0;i<=size;i++){
		if (tab[i]==val){
			return 1;
		}
	}
	return 0;
}

int rechercheDico(int tab[],int size, int val, int debut, int fin){
	if(debut==fin || debut>=TAILLE || fin<=0){
		return 0;
	}
	int i=(debut+fin)/2;
	if (val==tab[i]|| val==tab[debut] || val==tab[fin]){
		return 1;
	}
	if (val<tab[i]){
		return rechercheDico(tab,size,val,debut+1,i-1);
	}
	return rechercheDico(tab,size,val,i+1,fin-1);
}*/


int main(){
	int* tab=malloc(sizeof(int)*TAILLE);
	if (tab==NULL){
		exit(20);
	}
	fillArray(tab,TAILLE);
	//printArray(tab,TAILLE);
	int tri=tabTri(tab,TAILLE);
	printf("\nTrié=%d\n",tri);
	long start=0;
	long end=0;
	if(tri==0){
		start=getTimeMs();
		//triFusion(tab,TAILLE);
		triRapide(tab,TAILLE);
		end=getTimeMs();
	}
	long time=end-start;
	//printArray(tab,TAILLE);
	tri=tabTri(tab,TAILLE);
	printf("\nTrié=%d\n",tri);
	printf("\nTime=%ld\n",time);
	return 0;
}	
