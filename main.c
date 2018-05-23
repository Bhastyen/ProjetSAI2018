#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "GL/gl.h"
#include "GL/glut.h"

#include "camera.h"
#include "paraRectangle.h"
#include "snake.h"
#include "define.h"

#define PI 3.14156
#define LARGEUR 50
#define HAUTEUR 50


camera* c;
para* p;
snake* serpent;

void gestionClavier(unsigned char c, int x, int y);
void gestionSouris(int x, int y);
void Affichage();
void quadrillage();
void afficher_cube(int x1,int y1,int z1, int x2, int y2, int z2);


float Z = 0;
int main(int argc, char* argv[]){

    // creation de la camera
    c = creer_camera(5, 5, 5, 1, 1); // posx, posy, posz, vitesse, sensibilite
    
    // creation de l'environnement
    p = creer_para(2.0, 2.0, 2.0, 100.0, 100.0, 50.0);
    
    // creation du serpent
    serpent = creerSnake(creer_point(0, 0, 5), AXE_X);
    
    // initialisation de glut
    glutInit(&argc, argv);
    // initialisation du mode d'affichage
    glutInitDisplayMode(GLUT_RGBA | GLUT_SINGLE | GLUT_DEPTH);
    // position et taille de la fenetre
    glutInitWindowSize(800, 600);   // remplacer par glutFullScreen pour du pleine ecran
    glutInitWindowPosition(50, 50);
    // creation  de la fenetre
    glutCreateWindow("snake");
    // activation du z-buffer (gestion des faces cachees)
    glEnable(GL_DEPTH_TEST);
    // activation de l'affichage en donnant le nom de notre fonction gerant l'affichage
    glutIdleFunc(Affichage); 
    // definition de la fonction de gestion du clavier
    glutKeyboardFunc(gestionClavier);
    // definition de la fonction de gestion du deplacement de la souris passive
    glutPassiveMotionFunc(gestionSouris);
    // initialisation de la redirection des evenements vers les fonctions associees
    glutMainLoop();
    
    exit(0);
}


void Affichage(){
    point* tete = serpent->corps->debut_file->objet;
    
    // nettoyage de la fenetre et affichage du nettoyage
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    // definition de l'espace de dessin
    glMatrixMode(GL_PROJECTION);   // GL_MODELVIEW
    glLoadIdentity();
    
    // creation du volume de projection (Frustum)
    //gluPerspective(90, 90, 1, 50);
    glFrustum(-5, 5, -5, 5, 3, 50);
    // creation de la camera
    /*if (c->type == CAMERA_LIBRE)*/
        gluLookAt(getX(c->l_pos), getY(c->l_pos), getZ(c->l_pos), getX(c->l_cible), getY(c->l_cible), getZ(c->l_cible), 0, 0, 1);  
    /*else gluLookAt(getX(tete), getY(tete) - 2*serpent->rayon, getZ(tete) + 2*serpent->rayon, getX(c->s_cible), getY(c->s_cible), getZ(c->s_cible), 0, 0, 1);*/
        
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    // quadrillage representant le sol
    quadrillage();
    
    // envoie des points pour le cube
    //draw_para(p);
    
    afficherSnake(serpent);

    // envoie des donnees
    glFlush();
    
    // reaffichage
    glutPostRedisplay();
}


void gestionClavier(unsigned char ch, int x, int y){
    
    if (c->type == CAMERA_LIBRE){
        if (ch == 'z')
            deplacement(c, 'h');
        if (ch == 's')
            deplacement(c, 'b');
        if (ch == 'q')
            deplacement(c, 'g');
        if (ch == 'd')
            deplacement(c, 'd');
    }
    
    if (c->type == CAMERA_SERPENT){
        if (ch == 'z')
            deplacerSnake(serpent, 'h');
        if (ch == 'q')
            deplacerSnake(serpent, 'g');
        if (ch == 'd')
            deplacerSnake(serpent, 'd');
    }
            
    if (ch == 'f')
        change_camera(c);
        
}


void gestionSouris(int x, int y){
    
    orientation(c, x, y);
    
}


void afficher_cube(int x1,int y1,int z1, int x2, int y2, int z2){

	glBegin(GL_QUADS);
	glColor3f(0.9, 0.9, 0);
	glVertex3f(x1, y1, z1);
	glVertex3f(x2,y1, z1);
    glVertex3f(x2, y2, z1);
	glVertex3f(x1, y2, z1);


	glColor3f(0, 0.9, 0.9);
	glVertex3f(x1, y1, z2);
	glVertex3f(x1,y1, z1);
    glVertex3f(x2, y1, z1);
	glVertex3f(x2, y1, z2);

	glColor3f(0.9, 0, 0.9);
	glVertex3f(x2, y1, z2);
	glVertex3f(x2,y2 ,z2);
    glVertex3f(x2, y2, z1);
	glVertex3f(x2, y1, z1);

	// bleu
	glColor3f(0, 0, 0.9);
	glVertex3f(x1, y1, z2);
	glVertex3f(x1, y2, z2);
	glVertex3f(x2, y2, z2);
	glVertex3f(x2, y1, z2);
	// vert
	glColor3f(0, 0.9, 0);
	glVertex3f(x1, y1, z2);
	glVertex3f(x1, y2, z2);
	glVertex3f(x1, y2,z1);
	glVertex3f(x1, y1, z1);

	//rouge
	glColor3f(0.9, 0, 0);
	glVertex3f(x1, y2, z2);
	glVertex3f(x2, y2, z2);
    glVertex3f(x2, y2, z1);
	glVertex3f(x1, y2, z1);
	
	glEnd();
	
}


void quadrillage(){
	int i;
	
	glColor3f(1, 1, 0);
	for(i=-LARGEUR;i<=LARGEUR;i++){
		glBegin(GL_LINES);	
			glVertex3f(i, -HAUTEUR, 0);
			glVertex3f(i, HAUTEUR, 0);	
		glEnd();
	
	}
		
	//glColor3f(1, 0, 0);
	for(i=-HAUTEUR;i<=HAUTEUR;i++){
		glBegin(GL_LINES);	
			glVertex3f(LARGEUR, i, 0);
			glVertex3f(-LARGEUR, i, 0);	
		glEnd();
	
	}

}




