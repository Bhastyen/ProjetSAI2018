#ifndef SERPENT_H
#define SERPENT_H

#include "point.h"

void creerSnake(point* tete,int axe);
void creerFace(point* A,point* B,point* C,point* D);
void creerSphere(int rayon,point* position,float pas);
#endif
