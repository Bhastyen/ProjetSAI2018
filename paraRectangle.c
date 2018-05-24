#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "GL/gl.h"
#include "GL/glut.h"

#include "paraRectangle.h"


para* creer_para(float x, float y, float z, float tx, float ty, float tz){
    para* p = (para*) malloc(sizeof(para));
    if (p == NULL){
        fprintf(stderr, "paraRectangle.c::creer_para()::probleme d'allocation memoire\n");
        exit(-1);
    }
    
    p->pos = creer_point(x, y, z);
    p->t_aretes = creer_point(tx, ty, tz);

    return p;
}


void draw_para(para* p){
    float x1 = getX(p->pos); float y1 = getY(p->pos); float z1 = getZ(p->pos);
    float x2 = x1 + getX(p->t_aretes); float y2 = y1 + getY(p->t_aretes); float z2 = z1 + getZ(p->t_aretes);


    glBegin(GL_QUADS);

    // jaune: sol
	glColor3f(0.9, 0.9, 0);
	glVertex3f(x1, y1, z1);
	glVertex3f(x2, y1, z1);
    glVertex3f(x2, y2, z1);
	glVertex3f(x1, y2, z1);

    // turquoise: mur avant
	glColor3f(0, 0.9, 0.9);
	glVertex3f(x1, y1, z2);
	glVertex3f(x1, y1, z1);
    glVertex3f(x2, y1, z1);
	glVertex3f(x2, y1, z2);

    // violet: mur gauche
	glColor3f(0.9, 0, 0.9);
	glVertex3f(x2, y1, z2);
	glVertex3f(x2, y2 ,z2);
    glVertex3f(x2, y2, z1);
	glVertex3f(x2, y1, z1);

	// bleu: plafond
	glColor3f(0, 0, 0.9);
	glVertex3f(x1, y1, z2);
	glVertex3f(x1, y2, z2);
	glVertex3f(x2, y2, z2);
	glVertex3f(x2, y1, z2);
	
	// vert: mur droit
	glColor3f(0, 0.9, 0);
	glVertex3f(x1, y1, z2);
	glVertex3f(x1, y2, z2);
	glVertex3f(x1, y2, z1);
	glVertex3f(x1, y1, z1);

	//rouge: mur arriere
	glColor3f(0.9, 0, 0);
	glVertex3f(x1, y2, z2);
	glVertex3f(x2, y2, z2);
    glVertex3f(x2, y2, z1);
	glVertex3f(x1, y2, z1);
	
	glEnd();

}


