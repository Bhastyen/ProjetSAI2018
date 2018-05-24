#ifndef MON_H_FILE
#define MON_H_FILE
#include "../point.h"


typedef struct {
  double obj[7];// 0 --> type_objet (si 0 = cercle , 1=cube , 2=rectangle, 3= tube) 1--> position ( si 0 = centre cercle , 1 = bas gauche cube , 2 = bas gauche rectangle) 2--> (si 1 == largeur arete , 2 == largeur arete) 3--> ( 2->hauteur rectangle))
} type_objet;

typedef union {
	point* p ;
	type_objet* o;
	int indice;
} element;

typedef struct cellule{
  element objet;
  struct cellule* suivant;
}struct_cellule;//facultatif

typedef struct cellule_p{
  struct_cellule* debut_file;
  struct_cellule* fin_file;
}struct_suivit_cellule;

typedef struct_suivit_cellule* file;


/****************************
 *fonction : file creer_file_vide()
 ** Creer une file vide.
 ** Renvoie une element de type file;

 ***************************/
file creer_file_vide();

/****************************
 *fonction : int file_est_vide(file f)
 ** Informe si une file est vide ou non
 ** Renvoie 1 si vrai , 0 sinon
 ***************************/
int file_est_vide(file f);

/****************************
 *fonction : file enfile(file f,int element)
 ** Ajoute un element en fin de file
 ** Renvoi la file modifier

 ***************************/
file enfile(file f,element el);

/****************************
 *fonction : file vider_file(file f)
 ** Vide la file passer en parametre
 ** Retourne la file vide

 ***************************/
file vider_file(file f);

/****************************
 *fonction : int defile(file f)
 ** Enleve le premier element de la file
 ** Renvoie l'objet du premier element (int)

 ***************************/
element defile ( file f);

/****************************
 *fonction : void afficher_file(file f)
 ** Affiche la file

 ***************************/
void afficher_file(file f);

#endif
