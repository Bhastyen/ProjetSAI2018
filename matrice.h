#ifndef MATRICE_H_INCLUDED
#define MATRICE_H_INCLUDED

#include "point.h"


typedef struct {
    double** mat;
    int n;
    int m;
} matrice;


matrice* creer_matrice(int m, int n);

void remplir_matrice(matrice* mat, double** tab, int n, int m);

int get(matrice* m, int i, int j);
void set(matrice* m, int i, int j, double valeur);

matrice* multiplication_matrice(matrice* m1, matrice* m2);
point* multiplication_matrice_point(matrice* m, point* p);

matrice* detruire_matrice(matrice* m);


#endif
