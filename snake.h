#ifndef SERPENT_H
#define SERPENT_H

#include "./module/file.h"

typedef struct{
  file corps;
}snake;

snake* creerSnake(point* tete,int axe);
void creerBoudin(point* tete,int axe);
void creerFace(point* A,point* B,point* C,point* D);
void creerSphere(int rayon,point* position,float pas);
#endif
