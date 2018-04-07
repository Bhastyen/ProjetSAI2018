#include <stdio.h>
#include <stdlib.h>

#include "matrice.h"



matrice* creer_matrice(int m, int n){
    matrice* mat = NULL;
    int i; 
    
    mat = (matrice*) malloc(sizeof(matrice));
    if (mat == NULL){
        fprintf(stderr, "point.c::creer_matrice()::malloc de la matrice echoue\n");
        exit(-1);
    }
    
    mat->m = m;
    mat->n = n;
    
    mat->mat = (double**) malloc(n*sizeof(double*));
    if (mat->mat == NULL){
        fprintf(stderr, "point.c::creer_matrice()::malloc du tableau echoue\n");
        exit(-1);
    }
    
    for (i=0; i<n; i++){
        mat->mat[i] = (double*) malloc(m*sizeof(double));
        if (mat->mat[i] == NULL){
            fprintf(stderr, "point.c::creer_matrice()::malloc du tableau a la colonne %d echoue\n", i);
            exit(-1);
        }
    }
    
    return mat;
}

void remplir_matrice(matrice* mat, double** tab, int n, int m){  /* ne marche car ne possede pas la taille de la seconde dimension: a modifier*/
    int i,j;
    
    if (mat == NULL || m != mat->m || n != mat->n){
        fprintf(stderr, "point.c::remplir_matrice()::Erreur: soit la matrice est NULL soit les dimensions ne sont pas bonnes\n");
        exit(-1);
    }
    
    for (i = 0; i<n; i++){
        for (j = 0; j<m; j++){
            mat->mat[i][j] = tab[i][j];  
        }
    }

}

int get(matrice* m, int i, int j){
    if (m != NULL){
        return m->mat[i][j]; 
    }else{
        fprintf(stderr, "point.c::get()::Erreur: la matrice est NULL\n");
        exit(-1);
    }
}

void set(matrice* m, int i, int j, double valeur){
    if (m != NULL){
        m->mat[i][j] = valeur; 
    }else{
        fprintf(stderr, "point.c::set()::Erreur: la matrice est NULL\n");
        exit(-1);
    }
}


matrice* multiplication_matrice(matrice* m1, matrice* m2){
    int i,j,k;
    double somme;
    matrice* m3 = NULL;
        
    if (m1 == NULL || m2 == NULL || m1->m != m2->n){
        fprintf(stderr, "point.c::multiplication_matrice():: soit l'une des matrices est NULL soit elles ne sont pas compatibles pour la multiplication\n");
        exit(-1);
    }
    
    m3 = creer_matrice(m1->m, m2->n);

    for (i=0; i<m2->n; i++){
        for (j=0; j<m1->m; j++){
            somme = 0;
            for (k=0; k<m2->n; k++){
                somme += (m1->mat[i][k]*m2->mat[k][j]);
            }
            m3->mat[i][j] = somme;
        }
    }
    
    return m3;
}

point* multiplication_matrice_point(matrice* m, point* p){
    point* p2 = NULL;
        
    if (m == NULL || p == NULL){
        fprintf(stderr, "point.c::multiplication_matrice()::la matrice ou le point est NULL\n");
        exit(-1);
    }
    
    p2 = creer_point(1, m->n);

    p2->x = (m->mat[0][0]*p->x) + (m->mat[0][1]*p->y) + (m->mat[0][2]*p->z);
    p2->y = (m->mat[1][0]*p->x) + (m->mat[1][1]*p->y) + (m->mat[1][2]*p->z);
    p2->z = (m->mat[2][0]*p->x) + (m->mat[2][1]*p->y) + (m->mat[2][2]*p->z);
    
    return p2;
}


matrice* detruire_matrice(matrice* m){
    int i;
    
    if (m != NULL){
        for (i=0; i<m->n; i++){
            free(m->mat[i]);
        }
        
        free(m->mat);
        free(m);
    }else{
        fprintf(stderr, "point.c::detruire_matrice()::Erreur: la matrice est NULL\n");
        exit(-1);
    }
    
    return NULL;
}

