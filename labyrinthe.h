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
  int point_entree;
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


void calcul_position_point(int indice,piece_laby* p);
int adjacence_piece(int indice,
		    piece_laby liste_piece[LARGEUR*HAUTEUR*PROFONDEUR],
		    piece liste_types_pieces[63],
		    int laby[LARGEUR][HAUTEUR][PROFONDEUR],
		    file* candidats);
		 


void afficher_labyrinthe(file pieces_a_afficher,piece_laby liste_pieces[LARGEUR*HAUTEUR*PROFONDEUR]);

file file_piece_a_afficher_labyrinthe(piece_laby liste_pieces[LARGEUR*HAUTEUR*PROFONDEUR]);


void visualiser_piece_laby(piece_laby  p);
void visualiser_piece_laby_final(piece_laby p );
void visualiser_piece_laby_depart(piece_laby p);


void tracer_element_obj(element el);

void tracer_cube(element el,float transparence);

element creer_cube(point* p,int taille);

element creer_pomme(point* p);

void tracer_sphere(element el);

element creer_bonus(int mur);

void tracer_elements_piece(piece_laby piece_courante);

void deduire_position_element(element el,piece_laby piece_courante);



#endif
