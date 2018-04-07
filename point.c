#include <stdlib.h>
#include <stdio.h>

#include "point.h"



point* creer_point(float x, float y, float z){
    point* p = NULL;
    
    p = (point*) malloc(sizeof(point));
    if (p == NULL){
        fprintf(stderr, "point.c::creer_point()::malloc echoue\n");
        exit(-1);
    }
    
    p->x = x;
    p->y = y;
    p->z = z;
    p->w = 1;
    
    return p;
}

float getX(point* p){
    if (p != NULL){
        return p->x;
    }else{
        fprintf(stderr, "point.c::getX()::Erreur Point NULL\n");
        exit(-1);
    }
}

float getY(point* p){
    if (p != NULL){
        return p->y;
    }else{
        fprintf(stderr, "point.c::getY()::Erreur Point NULL\n");
        exit(-1);
    }
}

float getZ(point* p){
    if (p != NULL){
        return p->z;
    }else{
        fprintf(stderr, "point.c::getZ()::Erreur Point NULL\n");
        exit(-1);
    }
}

float getW(point* p){
    if (p != NULL){
        return p->w;
    }else{
        fprintf(stderr, "point.c::getW()::Erreur Point NULL\n");
        exit(-1);
    }
}


void setX(point* p, float x){
    if (p != NULL)
         p->x = x;
    else fprintf(stderr, "point.c::setX()::Attention votre point est NULL, valeur non affectee\n");
}


void setY(point* p, float y){
    if (p != NULL)
         p->y = y;
    else fprintf(stderr, "point.c::setY()::Attention votre point est NULL, valeur non affectee\n");
}

void setZ(point* p, float z){
    if (p != NULL)
         p->z = z;
    else fprintf(stderr, "point.c::setZ()::Attention votre point est NULL, valeur non affectee\n");
}

point* detruire_point(point* p){
    if (p != NULL)
        free(p);
    return NULL;
}

float** polygone(point** poly, int nb_point){
    float** poly2;
    int i;
    
    poly2 = (float**) malloc((nb_point+1)*sizeof(float*));
    if (poly2 == NULL)
        exit(-1); 
    
    for (i=0; i<nb_point+1; i++){
        poly2[i] = (float*) malloc(3*sizeof(float));
        if (poly2[i] == NULL)
            exit(-1); 
    }

    for (i=0; i<nb_point+1; i++){
        poly2[i][0] = poly[i%nb_point]->x;
        poly2[i][1] = poly[i%nb_point]->y;
        poly2[i][2] = poly[i%nb_point]->z;
    }
    
    return poly2;
}


