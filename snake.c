#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "GL/gl.h"
#include "GL/glut.h"

#include "snake.h"
#include "define.h"
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
/*
void creerBoudin(point* tete,int axe){
	int i ,decalageAxeX=0,decalageAxeY=0,decalageAxeZ=0;;
	if(axe==0){
	        for(i=0;i<5;i++){
		        creerSphere(2,creer_point(getX(tete)+decalageAxeX,getY(tete),getZ(tete)),20);
		        decalageAxeX+=2;
	        }
	}
	if(axe==1){
	        for(i=0;i<5;i++){
		        creerSphere(2,creer_point(getX(tete),getY(tete)+decalageAxeY,getZ(tete)),20);
		        decalageAxeY+=2;
	        }
	}
	if(axe==2){
	        for(i=0;i<5;i++){
		        creerSphere(2,creer_point(getX(tete),getY(tete),getZ(tete)+decalageAxeZ),20);
		        decalageAxeZ+=2;
	        }
	}
}*/

snake* creerSnake(point* tete,int axe){
	int i ,decalageAxeX=0,decalageAxeY=0,decalageAxeZ=0;
	point* tmp;
	snake* serpent = allocation_memoire(1,sizeof(snake));
	serpent->corps = enfile(serpent->corps,tete);
	
	if(axe==AXE_X){
	        for(i=0;i<5;i++){
		       tmp = creer_point(getX(tete)+decalageAxeX,getY(tete),getZ(tete));
		       serpent->corps = enfile(serpent->corps,tmp);
		       decalageAxeX+=2;
	        }
	}
	if(axe==AXE_Y){
	        for(i=0;i<5;i++){
	               tmp = creer_point(getX(tete),getY(tete)+decalageAxeY,getZ(tete));
		       serpent->corps = enfile(serpent->corps,tmp);
		       
		        decalageAxeY+=2;
	        }
	}
	if(axe==AXE_Z){
	        for(i=0;i<5;i++){
	               tmp = creer_point(getX(tete),getY(tete),getZ(tete)+decalageAxeZ);
		       serpent->corps = enfile(serpent->corps,tmp);
		   
		       decalageAxeZ+=2;
	        }
	}
	
	return serpent;
}

void afficherSnake(snake* serpent){
        struct_cellule* iterateur = serpent->corps->debut_file;
        
        while(iterateur != NULL){
            creerSphere(2,iterateur->objet,20);
            iterateur = iterateur->suivant;
        }
}

void deplacerSnake(snake* serpent,char direction,int axe_direction,int axe2){



}

}
