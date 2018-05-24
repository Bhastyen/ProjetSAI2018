#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "GL/gl.h"
#include "GL/glut.h"


#include "camera.h"
#define PI 3.14156


void init_positions(int positions[6]);
void init_axe_verticales(int axe_verticales[3]);


camera* creer_camera(float x, float y, float z, float vitesse, float sensibilite){
    camera* c = (camera*) malloc(sizeof(camera));
    if (c == NULL){
        fprintf(stderr, "camera.c::creer_camera()::probleme d'allocation memoire\n");
        exit(-1);
    }
    
    // option
    c->type = CAMERA_LIBRE;
    c->vitesse = vitesse;
    c->sensibilite = sensibilite;
    
    // angle de rotation
    c->l_phi = 0; c->l_theta = 0;
    c->s_phi = 0; c->s_theta = 0;
    
    // vecteur pour la camera libre
    c->l_pos = creer_point(x, y, z);
    c->l_vue = creer_point(0, 0, 0);
    c->l_cible = creer_point(0, 0, 0);
    c->l_deplLateral = creer_point(0, 0, 0);
    
    // vecteur pour la camera serpent
    c->s_pos = creer_point(x, y, z);
    c->s_vue = creer_point(0, 0, 0);
    c->s_cible = creer_point(0, 0, 0);
    c->s_deplLateral = creer_point(0, 0, 0);
    
    // valeur de deplacement de la souris
    c->xRel = 0; c->yRel = 0; c->xOld = 0; c->yOld = 0;
    
    // remplissage de la table
    init_positions(c->positions);
    init_axe_verticales(c->axe_verticales);

    return c;
}


void l_deplacement(camera* c, char direction){
    switch (direction){
    
        case 'h':
            // mise a jour de la position de la camera: avance en direction du point cible
            setX(c->l_pos, getX(c->l_pos)+getX(c->l_vue)*c->vitesse);
            setY(c->l_pos, getY(c->l_pos)+getY(c->l_vue)*c->vitesse);
            setZ(c->l_pos, getZ(c->l_pos)+getZ(c->l_vue)*c->vitesse);
            
            // mise a jour du point cible par la camera
            setX(c->l_cible, getX(c->l_vue)+getX(c->l_pos));
            setY(c->l_cible, getY(c->l_vue)+getY(c->l_pos));
            setZ(c->l_cible, getZ(c->l_vue)+getZ(c->l_pos));
            break;
        case 'b':
            // mise a jour de la position de la camera: avance dans le sens inverse du vecteur point cible
            setX(c->l_pos, getX(c->l_pos)-getX(c->l_vue)*c->vitesse);
            setY(c->l_pos, getY(c->l_pos)-getY(c->l_vue)*c->vitesse);
            setZ(c->l_pos, getZ(c->l_pos)-getZ(c->l_vue)*c->vitesse);
            
            // mise a jour du point cible par la camera
            setX(c->l_cible, getX(c->l_vue)+getX(c->l_pos));
            setY(c->l_cible, getY(c->l_vue)+getY(c->l_pos));
            setZ(c->l_cible, getZ(c->l_vue)+getZ(c->l_pos));
            break;
        case 'g':
            // mise a jour de la position de la camera: inverse du deplacement lateral par rapport vecteur vue (la normal du plan (vue, axe_vertical))
            setX(c->l_pos, getX(c->l_pos)-getX(c->l_deplLateral)*c->vitesse); 
            setY(c->l_pos, getY(c->l_pos)-getY(c->l_deplLateral)*c->vitesse);
            setZ(c->l_pos, getZ(c->l_pos)-getZ(c->l_deplLateral)*c->vitesse);
            
            // mise a jour du point cible par la camera
            setX(c->l_cible, getX(c->l_vue)+getX(c->l_pos));
            setY(c->l_cible, getY(c->l_vue)+getY(c->l_pos));
            setZ(c->l_cible, getZ(c->l_vue)+getZ(c->l_pos));
            break;
        case 'd':
            // mise a jour de la position de la camera: deplacement lateral par rapport au vecteur vue (la normal du plan (vue, axe_vertical))
            setX(c->l_pos, getX(c->l_pos)+getX(c->l_deplLateral)*c->vitesse); 
            setY(c->l_pos, getY(c->l_pos)+getY(c->l_deplLateral)*c->vitesse);
            setZ(c->l_pos, getZ(c->l_pos)+getZ(c->l_deplLateral)*c->vitesse);
            
            // mise a jour du point cible par la camera
            setX(c->l_cible, getX(c->l_vue)+getX(c->l_pos));
            setY(c->l_cible, getY(c->l_vue)+getY(c->l_pos));
            setZ(c->l_cible, getZ(c->l_vue)+getZ(c->l_pos));
            break;
        default: 
            break;
    }
    
}



void s_deplacement(camera* c, char direction){
    
}


void deplacement(camera* c, char direction){

    if (c->type == CAMERA_LIBRE)
        l_deplacement(c, direction);
    else s_deplacement(c, direction);

}


void change_camera(camera* c){

    if (c->type == CAMERA_LIBRE){
        c->type = CAMERA_SERPENT;
    }else{
        c->type = CAMERA_LIBRE;
        
        // se place au meme endroit que la camera serpent
        /*c->l_phi = c->s_phi; c->l_theta = c->s_theta;
        c->l_pos->x = c->s_pos->x; c->l_pos->y = c->s_pos->y; c->l_pos->z = c->s_pos->z;
        c->l_vue->x = c->s_vue->x; c->l_vue->y = c->s_vue->y; c->l_vue->z = c->s_vue->z;
        c->l_cible->x = c->s_cible->x; c->l_cible->y = c->s_cible->y; c->l_cible->z = c->s_cible->z;
        c->l_deplLateral->x = c->s_deplLateral->x; c->l_deplLateral->y = c->s_deplLateral->y; c->l_deplLateral->z = c->s_deplLateral->z;    */        
    }

}


void l_orientation(camera* c){
    float norme;
    
    // mise a jour des angles symbolisant la direction vers laquelle je regarde 
    c->l_theta += -c->xRel*c->vitesse;
    c->l_phi += -c->yRel*c->vitesse;
    
    // bloque la camera lorsque je regarde en l'air ou en bas
    if (c->l_phi > 89)
        c->l_phi = 89;
    else if (c->l_phi < -89)
        c->l_phi = -89;
        
    // calcul du vecteur vue a partir des coordonnees spheriques
    // Attention: le calcul change suivant dans quel parti de la sphere le vecteur est "situe"
    if (getX(c->l_vue) == 1.0){
        setX(c->l_vue, sin(c->l_phi*(PI/180.0)));
        setY(c->l_vue, cos(c->l_phi*(PI/180.0)) * cos(c->l_theta*(PI/180.0)));
        setZ(c->l_vue, cos(c->l_phi*(PI/180.0)) * sin(c->l_theta*(PI/180.0)));
    }else if (getY(c->l_vue) == 1.0){
        setX(c->l_vue, cos(c->l_phi*(PI/180.0)) * sin(c->l_theta*(PI/180.0)));
        setY(c->l_vue, sin(c->l_phi*(PI/180.0)));
        setZ(c->l_vue, cos(c->l_phi*(PI/180.0)) * cos(c->l_theta*(PI/180.0)));
    }else{
        setX(c->l_vue, cos(c->l_phi*(PI/180.0)) * cos(c->l_theta*(PI/180.0)));
        setY(c->l_vue, cos(c->l_phi*(PI/180.0)) * sin(c->l_theta*(PI/180.0)));
        setZ(c->l_vue, sin(c->l_phi*(PI/180.0)));
    }
    
    // normalisation du vecteur vue
    // calcul de la norme de vue
    norme = sqrt(getX(c->l_vue)*getX(c->l_vue) + getY(c->l_vue)*getY(c->l_vue) + getZ(c->l_vue)*getZ(c->l_vue));
    setX(c->l_vue, getX(c->l_vue)/norme); setY(c->l_vue, getY(c->l_vue)/norme); setZ(c->l_vue, getZ(c->l_vue)/norme);
    
    // calcul du vecteur lateral au vecteur vue: produit vectoriel
    setX(c->l_deplLateral, getY(c->l_vue)*1.0f-getZ(c->l_vue)*0.0f);   //y*z' - z*y'
    setY(c->l_deplLateral, getZ(c->l_vue)*0.0f-getX(c->l_vue)*1.0f);   //z*x' - x*z'
    setZ(c->l_deplLateral, getX(c->l_vue)*0.0f-getY(c->l_vue)*0.0f);   //x*y' - y*x'
    // normalisation de dplLateral
    norme = sqrt(getX(c->l_deplLateral)*getX(c->l_deplLateral) + getY(c->l_deplLateral)*getY(c->l_deplLateral) + getZ(c->l_deplLateral)*getZ(c->l_deplLateral));
    setX(c->l_deplLateral, getX(c->l_deplLateral)/norme); setY(c->l_deplLateral, getY(c->l_deplLateral)/norme); setZ(c->l_deplLateral, getZ(c->l_deplLateral)/norme);
    
    // calcul le nouveau point cible
    setX(c->l_cible, getX(c->l_vue)+getX(c->l_pos));
    setY(c->l_cible, getY(c->l_vue)+getY(c->l_pos));
    setZ(c->l_cible, getZ(c->l_vue)+getZ(c->l_pos));

}

void s_orientation(camera* c){
    
    // mise a jour des angles symbolisant la direction vers laquelle je regarde 
    c->l_theta += -c->xRel*c->vitesse;
    c->l_phi += -c->yRel*c->vitesse;
    
    // bloque la camera lorsque je regarde en l'air ou en bas
    if (c->s_phi > 89)
        c->s_phi = 89;
    else if (c->s_phi < -89)
        c->s_phi = -89;

}

void orientation(camera* c, int x, int y){
    
    // mets a jour les coordonnees relative de la souris: difference entre les nouvelles coordonnees et les anciennes 
    if (c->xOld != 0.0 || c->yOld != 0.0){
        c->xRel = x-c->xOld; c->yRel = y-c->yOld;
        c->xOld = x; c->yOld = y;
    }
    c->xOld = x; c->yOld = y;
    
    if (c->type == CAMERA_LIBRE)
        l_orientation(c);
    else s_orientation(c);
    
}


void init_positions(int positions[6]){
    positions[SOL] = AXE_Z;
    positions[PLAFOND] = AXE_Z_BIS;
    positions[MUR_A] = AXE_Y;
    positions[MUR_AR] = AXE_Y_BIS;
    positions[MUR_G] = AXE_X;
    positions[MUR_D] = AXE_X_BIS;
}



void init_axe_verticales(int axe_verticales[3]){
    axe_verticales[SOL] = AXE_Z;
    axe_verticales[PLAFOND] = AXE_Z_BIS;
    axe_verticales[MUR_G] = AXE_X;
    axe_verticales[MUR_D] = AXE_X_BIS;
    axe_verticales[MUR_A] = AXE_Y;
    axe_verticales[MUR_AR] = AXE_Y_BIS;
}
    
    

