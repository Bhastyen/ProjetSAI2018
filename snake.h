#ifndef SERPENT_H
#define SERPENT_H

#include "./module/file.h"
#include "./module/mon_allocation.h"
typedef struct{
  file corps;
}snake;

snake* creerSnake(point* tete,int axe);
void creerBoudin(point* tete,int axe);
void creerFace(point* A,point* B,point* C,point* D);
void afficherSphere(int rayon,point* position,float pas);
void afficherSnake(snake* serpent);
#endif
