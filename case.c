///gestion d'1 case
 
#include <stdio.h>
#include <math.h>
#include <stdlib.h>  
#include <unistd.h>
#include <time.h>
#include <sys/time.h>
#include <string.h>

typedef enum {MONSTRE, COFFRE, ARME, TOTEM}Type;//nature de la case
typedef enum {BASILIC, TROLL, ZOMBIE, HARPIE}Monstre; //monstres 
typedef enum {EPEE, BATON, GRIMOIRE, DAGUE}Arme; //armes antiques
typedef enum {TORCHE,BOUCLIER,HACHE,ARC}Outil; //armes équipables

struct {
	Type type;
	Coordonnées position;
	Statut statut;
	
}Case;

