#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include "GL/gl.h"
#include "GL/glut.h"

#include "camera.h"
#include "paraRectangle.h"
#include "snake.h"
#include "define.h"

#define PI 3.14156
#define LARGEUR 50
#define HAUTEUR 50



// objet de la scene
camera* c;
para* p;
snake* serpent;

// caracteristique de la partie
int game_over = 0;
int score = 0;
int fin_partie = 0;
clock_t temps = 0;

// prototypes
void affiche_score(float x ,float y, float z, char* score);
void affiche_temps(float x ,float y, float z, char* temps_h, char* temps_m, char* temps_s);
void affichage_game_over(float x ,float y, float z, char* score, char* temps_h, char* temps_m, char* temps_s);
void affichage_fin_partie(float x ,float y, float z, char* score, char* temps_h, char* temps_m, char* temps_s);
char* itoa(int entier);
void gestionClavier(unsigned char c, int x, int y);
void gestionSouris(int x, int y);
void Affichage();
void quadrillage();
void afficher_cube(int x1,int y1,int z1, int x2, int y2, int z2);


int main(int argc, char* argv[]){

    // creation de la camera
    c = creer_camera(5, 5, 5, 1, 1); // posx, posy, posz, vitesse, sensibilite
    
    // creation de l'environnement
    p = creer_para(-10.0, -10.0, -10.0, 30.0, 30.0, 30.0);
    
    // creation du serpent
    serpent = creerSnake(creer_point(0, 0, 5), AXE_X);
    
    
    // initialisation de glut
    glutInit(&argc, argv);
    // initialisation du mode d'affichage
    glutInitDisplayMode(GLUT_RGBA | GLUT_SINGLE | GLUT_DEPTH);
    // position et taille de la fenetre
    glutInitWindowSize(F_L, F_H);   // remplacer par glutFullScreen pour du pleine ecran
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
    // chaine permettant d'afficher les informations
    char* ch_score; char* ch_temps_h;
    char* ch_temps_m; char* ch_temps_s;
   
    // sert a calculer le point cible et la position de la camera_serpent
    point* avant_tete = element_file(serpent->corps, 0);
    point* cible_serpent = serpent->axes[serpent->axe];
    point* position = serpent->axes[c->positions[serpent->face]];
    point* axe_verticale = serpent->axes[c->axe_verticales[serpent->face]];
    
    // calcul la position de la camera du serpent et son point cible
    float x = getX(avant_tete)+4*serpent->rayon*getX(position);
    float y = getY(avant_tete)+4*serpent->rayon*getY(position);
    float z = getZ(avant_tete)+4*serpent->rayon*getZ(position);
    
    float cx = getX(avant_tete)+4*serpent->vitesse*getX(cible_serpent);
    float cy = getY(avant_tete)+4*serpent->vitesse*getY(cible_serpent);
    float cz = getZ(avant_tete)+4*serpent->vitesse*getZ(cible_serpent);
    
    
    // nettoyage de la fenetre et affichage du nettoyage
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    // definition de l'espace de dessin
    glMatrixMode(GL_PROJECTION);   // GL_MODELVIEW
    glLoadIdentity();
    
    // creation du volume de projection (Frustum)
    glFrustum(-2, 2, -2, 2, 1, 50);
    // parametrage de la camera
    if (c->type == CAMERA_LIBRE)
        gluLookAt(getX(c->l_pos), getY(c->l_pos), getZ(c->l_pos), getX(c->l_cible), getY(c->l_cible), getZ(c->l_cible), 0, 0, 1);  
    else gluLookAt(x, y, z, cx, cy, cz, getX(axe_verticale), getY(axe_verticale), getZ(axe_verticale));
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    // quadrillage representant le sol
    quadrillage();
    
    // envoie des points pour le cube
    draw_para(p);
    
    // affiche le serpent
    afficherSnake(serpent);

    // calcule du temps de jeux
    if (game_over != 1 && fin_partie != 1)
        temps = clock();

    // affiche les infos a l'ecran
    ch_score = itoa(score);
    ch_temps_h = itoa((temps/CLOCKS_PER_SEC)/3600);
    ch_temps_m = itoa(((temps/CLOCKS_PER_SEC)%3600)/60);
    ch_temps_s = itoa(((temps/CLOCKS_PER_SEC)%3600)%60);
    
    if (game_over != 1 && fin_partie != 1){
        affiche_score(cx+2.5*getX(axe_verticale), cy+2.5*getY(axe_verticale), cz+2.5*getZ(axe_verticale), ch_score);
        affiche_temps(cx+5.*getX(axe_verticale), cy+5.*getY(axe_verticale), cz+5.*getZ(axe_verticale), ch_temps_h, ch_temps_m, ch_temps_s);
    }
    
    // regarde si la partie est terminee
    if (game_over == 1){
         affichage_game_over(cx+2.5*getX(axe_verticale), cy+2.5*getY(axe_verticale), cz+2.5*getZ(axe_verticale), ch_score, ch_temps_h, ch_temps_m, ch_temps_s);
    }else if (fin_partie == 1){
         affichage_fin_partie(cx+2.5*getX(axe_verticale), cy+2.5*getY(axe_verticale), cz+2.5*getZ(axe_verticale), ch_score, ch_temps_h, ch_temps_m, ch_temps_s);
    }

    // envoie des donnees
    glFlush();
    
    // reaffichage
    glutPostRedisplay();
}


void gestionClavier(unsigned char ch, int x, int y){
    int r = VIDE;   // resultat du deplacement
    
    if (game_over == 1 || fin_partie == 1){
        if (ch == 27 || ch == 13){
            exit(0);
        }
        
        return ;
    }
    
    if (ch == 27 || ch == 13){
        //glutDestroyWindow()
        exit(0);
    }
    
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
            r = deplacerSnake(serpent, p, 'h');
        if (ch == 'q')
            r = deplacerSnake(serpent, p, 'g');
        if (ch == 'd')
            r = deplacerSnake(serpent, p, 'd');
    }
            
    if (ch == 'f')
        change_camera(c);
    
    if (r == GAME_OVER)
        game_over = 1;
    if (r == SCORE1)
        score += SCORE1;
    if (r == SCORE2)
        score += SCORE2;
    if (r == SCORE3)
        score += SCORE3;
    if (r == FINI){
        fin_partie = 1; 
        score += FINI;
    }
      
}


void gestionSouris(int x, int y){
    
    orientation(c, x, y);
    
}

// permet d'afficher un quadrillage representant le sol
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


// fonction d'affichage des differentes informations

void affiche_score(float x ,float y, float z, char* score){
    int i = 0;
    
    // positionne premier caractere
    glColor3f(1.0f, 0.258f, 0.0f);
    glRasterPos3f(x, y, z);
    while (score[i] != '\0'){ 
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, score[i]);
        i ++;
    }
    
}

void affiche_temps(float x ,float y, float z, char* temps_h, char* temps_m, char* temps_s){  
    int i = 0;
    char message[1024] = "";
    
    // creation de la chaine
    strcat(message, temps_h);
    strcat(message, ":");
    strcat(message, temps_m);
    strcat(message, ":");
    strcat(message, temps_s);
    
    // positionne premier caractere
    glColor3f(1.0f, 0.258f, 0.0f);
    glRasterPos3f(x, y, z);
    while (message[i] != '\0'){ 
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, message[i]);
        i ++;
    }

}

void affichage_game_over(float x ,float y, float z, char* score, char* temps_h, char* temps_m, char* temps_s){
    int i = 0;
    
    // construction du message a afficher
    char message1[1024] = "Vous avez perdu dommage! ";
    strcat(message1, "Votre score est de "); 
    strcat(message1, score);
    strcat(message1, "   Votre temps est de ");
    strcat(message1, temps_h);
    strcat(message1, ":");
    strcat(message1, temps_m);
    strcat(message1, ":");
    strcat(message1, temps_s);
    
    
    glColor3f(1.0f, 0.258f, 0.0f);
    // positionne premier caractere
    glRasterPos3f(x, y, z);
    while (message1[i] != '\0'){ 
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, message1[i]);
        i ++;
    }

}

    
void affichage_fin_partie(float x ,float y, float z, char* score, char* temps_h, char* temps_m, char* temps_s){
    int i = 0;
    
    // construction du message a afficher
    char message1[1024] = "Vous avez gagne felicitation! ";
    strcat(message1, "Votre score est de "); 
    strcat(message1, score);
    strcat(message1, "   Votre temps est de ");
    strcat(message1, temps_h);
    strcat(message1, ":");
    strcat(message1, temps_m);
    strcat(message1, ":");
    strcat(message1, temps_s);
    
    
    glColor3f(1.0f, 0.258f, 0.0f);
    // positionne premier caractere
    glRasterPos3f(x, y, z);
    while (message1[i] != '\0'){ 
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, message1[i]);
        i ++;
    }
    
}
    

char* itoa(int entier){
    int i = 0;
    int taille;
    char* resultat;
    
    if (entier == 0)
        taille = 1;
    else taille = log10(entier)+1;
    
    resultat = (char*) malloc(sizeof(char)*taille+1);
    if (resultat == NULL){
         fprintf(stderr, "main.c::itoa()::probleme allocation memoire\n");
         exit(-1);
    }
    
    resultat[taille] = '\0';
    
    if (entier != 0){
        while (resultat[i] != '\0'){
            resultat[i] = '0' + (entier / ((int) pow(10, (taille-1)-i)));
            entier = entier % ((int) pow(10, (taille-1)-i));
            i ++;
        }
    }else{
        resultat[0] = '0';
    }

    return resultat;
}   





