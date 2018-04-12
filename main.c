#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "GL/gl.h"
#include "GL/glut.h"

#include "paraRectangle.h"
#include "snake.h"

#define PI 3.14156
#define LARGEUR 10
#define HAUTEUR 10




int sens = 1;

float vitesse_camera = 1.0f;
float theta = 0.0f; float phi = 0.0f;
float posx = 0.0; float posy = 0.0; float posz = 0.0;
float vuex = 0.0; float vuey = 0.0; float vuez = 0.0;
float ciblex = 0.0; float cibley = 0.0; float ciblez = 0.0;
float deplLateralx = 0.0f; float deplLateraly = 0.0f; float deplLateralz = 0.0f;

int xRel = 0, yRel = 0; int xOld = 0, yOld = 0;


para* p;


void gestionClavier(unsigned char c, int x, int y);
void gestionSouris(int x, int y);
void Affichage();
void quadrillage();
void afficher_cube(int x1,int y1,int z1, int x2, int y2, int z2);


float Z = 0;
int main(int argc, char* argv[]){

    p = creer_para(2.0, 2.0, 2.0, 20.0, 20.0, 3.0);
    
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
    
    // variation de theta
    /*if (theta < 360.0f)
        theta += sens*0.05f;
    else theta = 0.0f;*/
    
    // nettoyage de la fenetre et affichage du nettoyage
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    // definition de l'espace de dessin
    glMatrixMode(GL_PROJECTION);   // GL_MODELVIEW
    glLoadIdentity();
    
    // creation du volume de projection (Frustum)
    //glperpective(90, 90);
    glFrustum(-5, 5, -5, 5, 3, 50);
    // creation de la camera
    //gluLookAt(5*cos(theta*(PI/180.0)), 10*sin(theta*(PI/180.0)), 20, 0, 0, 0, 0, 0, 1);
    gluLookAt(posx, posy, posz, ciblex, cibley, ciblez, 0, 0, 1);    //, 30, posy,
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    // quadrillage representant le sol
    quadrillage();
    
    // envoie des points pour le cube
    draw_para(p);
    //afficher_cube(-1.0, -1.0, -1.0, 1.0, 1.0, 1.0);
     creerSnake(creer_point(Z,0,0),0);
     Z+=0.5;
     if(Z==30.0)Z=0;
    // envoie des donnees
    glFlush();
    
    // reaffichage
    glutPostRedisplay();
}


void gestionClavier(unsigned char c, int x, int y){
    
    if (c == 'z'){
        // mise a jour de la position de la camera: avance en direction du point cible
        posx += vuex*vitesse_camera;
        posy += vuey*vitesse_camera; 
        posz += vuez*vitesse_camera;
        
        // mise a jour du point cible par la camera
        ciblex = posx+vuex;
        cibley = posy+vuey;
        ciblez = posz+vuez;
    }
        
    if (c == 'q'){
        // mise a jour de la position de la camera: inverse du deplacement lateral par rapport vecteur vue (la normal du plan (vue, axe_vertical))
        posx -= deplLateralx*vitesse_camera; 
        posy -= deplLateraly*vitesse_camera; 
        posz -= deplLateralz*vitesse_camera;
        
        // mise a jour du point cible par la camera
        ciblex = posx+vuex;
        cibley = posy+vuey;
        ciblez = posz+vuez;
    }
        
    if (c == 's'){
        // mise a jour de la position de la camera: avance dans le sens inverse du vecteur point cible
        posx -= vuex*vitesse_camera; 
        posy -= vuey*vitesse_camera; 
        posz -= vuez*vitesse_camera;
        
        // mise a jour du point cible par la camera
        ciblex = posx+vuex;
        cibley = posy+vuey;
        ciblez = posz+vuez;
    }
    
    if (c == 'd'){
        // mise a jour de la position de la camera: deplacement lateral par rapport au vecteur vue (la normal du plan (vue, axe_vertical))
        posx += deplLateralx*vitesse_camera; 
        posy += deplLateraly*vitesse_camera; 
        posz += deplLateralz*vitesse_camera;
        
        // mise a jour du point cible par la camera
        ciblex = posx+vuex;
        cibley = posy+vuey;
        ciblez = posz+vuez;
    }
    
}


void gestionSouris(int x, int y){
    float vitesse = 0.3;
    float norme;
    
    // calcul des coordonnees relative de la souris: difference entre les nouvelles coordonnees et les anciennes 
    if (xOld != 0.0 || yOld != 0.0){
        xRel = x-xOld; yRel = y-yOld;
        xOld = x; yOld = y;
    }
    xOld = x; yOld = y;
    
    // mise a jour des angles symbolisant la direction vers laquelle je regarde 
    theta += -xRel*vitesse;
    phi += -yRel*vitesse;
    
    // bloque la camera lorsque je regarde en l'air ou en bas
    if (phi > 89)
        phi = 89;
    else if (phi < -89)
        phi = -89;
    
    // calcul du vecteur vue a partir des coordonnees spheriques
    // Attention: le calcul change suivant dans quel parti de la sphere le vecteur est "situe"
    if (vuex == 1.0){
        vuex = sin(phi*(PI/180.0));
        vuey = cos(phi*(PI/180.0)) * cos(theta*(PI/180.0));
        vuez = cos(phi*(PI/180.0)) * sin(theta*(PI/180.0));
    }else if (vuey == 1.0){
        vuex = cos(phi*(PI/180.0)) * sin(theta*(PI/180.0));
        vuey = sin(phi*(PI/180.0));
        vuez = cos(phi*(PI/180.0)) * cos(theta*(PI/180.0));
    }else{
        vuex = cos(phi*(PI/180.0)) * cos(theta*(PI/180.0));
        vuey = cos(phi*(PI/180.0)) * sin(theta*(PI/180.0));
        vuez = sin(phi*(PI/180.0));
    }
    
    // normalisation du vecteur vue
    // calcul de la norme de vue
    norme = sqrt(vuex*vuex + vuey*vuey + vuez*vuez);
    vuex /= norme; vuey /= norme; vuez /= norme;
    
    // calcul du vecteur lateral au vecteur vue
    deplLateralx = vuey*1.0f-vuez*0.0f;   //y*z' - z*y'
    deplLateraly = vuez*0.0f-vuex*1.0f;   //z*x' - x*z'
    deplLateralz = vuex*0.0f-vuey*0.0f;   //x*y' - y*x'
    // normalisation de dplLateral
    norme = sqrt(deplLateralx*deplLateralx + deplLateraly*deplLateraly + deplLateralz*deplLateralz);
    deplLateralx /= norme; deplLateraly /= norme; deplLateralz /= norme;
    
    // calcul le nouveau point cible
    ciblex = posx+vuex; 
    cibley = posy+vuey; 
    ciblez = posz+vuez;
    
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
	int i,j;
	
	//glColor3f(0, 0, 0.9);
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




