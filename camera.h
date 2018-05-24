#ifndef CAMERA_H
#define CAMERA_H

#define CAMERA_SERPENT 1
#define CAMERA_LIBRE 2

#include "point.h"
#include "define.h"


typedef struct {
    int type;
    
    // vitesse
    float vitesse;
    float sensibilite;
    
    // orientation de la camera
    float l_phi, l_theta;
    float s_phi, s_theta;
    
    // vecteurs
    point* l_pos, *l_vue, *l_cible, *l_deplLateral;
    point* s_pos, *s_vue, *s_cible, *s_deplLateral;
    
    // valeur de deplacement de la souris
    int xRel, yRel; int xOld, yOld;
    
    // tableau definissant la position de la camera du serpent suivant la face du serpent
    int positions[6];
    int axe_verticales[3];
    
} camera;



camera* creer_camera(float x, float y, float z, float vitesse, float sensibilite);

void deplacement(camera* c, char direction);

void change_camera(camera* c);

void orientation(camera* c, int x, int y);


#endif
