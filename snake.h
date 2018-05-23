#ifndef SERPENT_H
#define SERPENT_H

#include "./module/file.h"
#include "./module/mon_allocation.h"

typedef struct{
  // file de point pour le corps 
  file corps;
  
  // vitesse
  int rayon;
  int vie;
  float vitesse;
  
  // orientation du serpent
  int directions[3][6];
  int redirection[6][3];
  point* axes[6];
  
  // info
  int axe, type_face, face;
  
} snake;



snake* creerSnake(point* tete,int axe);
int deplacerSnake(snake* serpent, char direction);
int collision_serpent(file corps, point* tete, int rayon);

void creerBoudin(point* tete,int axe);

// fonction d'affichage du serpent
void afficherFace(point* A,point* B,point* C,point* D);
void afficherSphere(int rayon,point* position,float pas);
void afficherSnake(snake* serpent);


#endif
