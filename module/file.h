#ifndef MON_H_FILE
#define MON_H_FILE
#include "../point.h"

typedef point* element;

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
 *fonction : element dernier_file(file f)
 ** renvoie le dernier element de la file

 ***************************/
element dernier_file ( file f);

/****************************
 *fonction : void afficher_file(file f)
 ** Affiche la file

 ***************************/
void afficher_file(file f);

#endif
