#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "GL/gl.h"
#include "GL/glut.h"


#include "snake.h"
#define PI 3.14156



void creerFace(point* A,point* B,point* C,point* D){
	fprintf(stderr,"A %f %f %f\n",getX(A),getY(A),getZ(A));
	fprintf(stderr,"B %f %f %f\n",getX(B),getY(B),getZ(B));
	fprintf(stderr,"C %f %f %f\n",getX(C),getY(C),getZ(C));
	fprintf(stderr,"D %f %f %f\n",getX(D),getY(D),getZ(D));
    glBegin(GL_QUADS);

    // jaune
	glColor3f(0.9, 0.9, 0);
	glVertex3f(getX(A), getY(A), getZ(A));
	glVertex3f(getX(B), getY(B), getZ(B));
    glVertex3f(getX(C), getY(C), getZ(C));
	glVertex3f(getX(D), getY(D), getZ(D));
	
	glEnd();

}
void creerSphere(int rayon,point* position,float pas){
	float deltaO = (2*PI)/(float)pas;
	float deltaL = deltaO;
	float teta,phy;
	for(teta =0; teta < 2*PI ; teta+=deltaO){
		for(phy = 0 ; phy < PI/2 ; phy+=deltaL){fprintf(stderr,"deltaO %f teta %f phy %f\n",deltaO,teta,phy);
			creerFace(creer_point_angle_pos(teta,phy,rayon,position),
					  creer_point_angle_pos(teta+deltaO,phy,rayon,position),
					  creer_point_angle_pos(teta+deltaO,phy+deltaL,rayon,position),
					  creer_point_angle_pos(teta,phy+deltaL,rayon,position));
			
			
			creerFace(creer_point_angle_pos(teta,-phy,rayon,position),
					  creer_point_angle_pos(teta+deltaO,-phy,rayon,position),
					  creer_point_angle_pos(teta+deltaO,-phy-deltaL,rayon,position),
					  creer_point_angle_pos(teta,-phy-deltaL,rayon,position));
		
		}
	}fprintf(stderr,"ici fini\n");
}

void creerSnake(point* tete,int axe){
	int i ,decalageAxeX=0;
	
	for(i=0;i<5;i++){
		creerSphere(2,creer_point(getX(tete)+decalageAxeX,getY(tete),getZ(tete)),20);
		decalageAxeX+=2;
	}

}


