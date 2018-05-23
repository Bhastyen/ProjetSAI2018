#ifndef LABYRINTHE_H_INCLUDED
#define LABYRINTHE_H_INCLUDED

#include "point.h"
#include "./module/file.h"
#include "define.h"

typedef struct {
  point* pos_bg; //position bas "gauche" de la piece
  int taille;
  int type_piece;
} piece_laby;

typedef struct {

 int murs[6]; //Determine la presence des differentes murs
 file objets;//une liste d'objets
 
} piece;

/*
element obj ;
obj.o = mon_allocation(1,sizeog(objet));
piece.objets = enfile(piece.objets,
*/
void initilisation_type_piece(piece liste_pieces[63]);
void afficher_result(piece liste_pieces[63]);

void init_type_pieces_bis(piece liste_pieces[63] ,int nombre_murs,int indice_depart,int indice_depart_nouveau ,int nombre_combinaisons);

void visualiser_type_piece(piece  p);
#endif
