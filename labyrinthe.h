#ifndef LABYRINTHE_H_INCLUDED
#define LABYRINTHE_H_INCLUDED

#include "point.h"
#include "./module/file.h"
#include "define.h"

// x largeur , z hauteur , y profondeur
typedef struct {
  point* pos_bg; //position bas "gauche" de la piece
  int taille;
  int type_piece;
  int murs[6];
  file adjacent;
  int longueur_chemin;
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
void initilisation_type_piece(piece liste_types_pieces[63]);
void afficher_result(piece liste_types_pieces[63]);

void init_type_pieces_bis(piece liste_pieces[63] ,int nombre_murs,int indice_depart,int indice_depart_nouveau ,int nombre_combinaisons);

void visualiser_type_piece(piece  p);

void initilisation_labyrinthe(int laby[LARGEUR][HAUTEUR][PROFONDEUR]);


void creer_labyrinthe(piece_laby liste_pieces[LARGEUR*HAUTEUR*PROFONDEUR]);

void determine_i_k_j(int indice,int* i,int* k,int* j);

int calcul_indice(int i,int k,int j);

void calcul_position_point(int indice,point* p);

int adjacence_piece(piece_laby piece_courante,
		    int indice,
		    piece_laby liste_piece[LARGEUR*HAUTEUR*PROFONDEUR],
		    piece liste_types_pieces[63],
		    int laby[LARGEUR][HAUTEUR][PROFONDEUR],
		    file candidats);
		 
void visualiser_piece_laby(piece_laby  p);
void afficher_labyrinthe(piece_laby liste_pieces[LARGEUR*HAUTEUR*PROFONDEUR]);
#endif
