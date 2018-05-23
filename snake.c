#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "GL/gl.h"
#include "GL/glut.h"

#include "snake.h"
#include "define.h"
#define PI 3.14156


int axe_inverse(int axe);
void init_redirection(int redirection[6][3]);
void init_directions(int directions[3][6]);
void init_axes(point* axes[6]);


snake* creerSnake(point* tete, int axe){
	int i=0 ,decalageAxeX=0, decalageAxeY=0, decalageAxeZ=0;
	point* tmp;
	snake* serpent = allocation_memoire(1, sizeof(snake));

    // initialisation des caracteristiques
    serpent->rayon = 1;
    serpent->vie = TAILLE;
    serpent->vitesse = serpent->rayon;

    // information sur le serpent pour le deplacement
    serpent->axe = axe;
    serpent->type_face = SOL;
    serpent->face = SOL;
    
    // tableau permettant de connaitre les transitions possibles lors des deplacements
    init_directions(serpent->directions);
    init_redirection(serpent->redirection);
    init_axes(serpent->axes);

	// creation du corps du serpent parallele a un axe au choix
	if(axe == AXE_X){
			decalageAxeX = serpent->rayon*(TAILLE-1);
	        for(i=1;i<TAILLE;i++){
	           tmp = creer_point(getX(tete)-decalageAxeX, getY(tete), getZ(tete));
		       serpent->corps = enfile(serpent->corps, tmp);
		       decalageAxeX -= serpent->rayon;
	        }
	}
	
	if(axe == AXE_Y){
			decalageAxeY = serpent->rayon*(TAILLE-1);
	        for(i=1;i<TAILLE;i++){
	            tmp = creer_point(getX(tete),getY(tete)-decalageAxeY,getZ(tete));
		        serpent->corps = enfile(serpent->corps,tmp);
		        decalageAxeY -= serpent->rayon;
	        }
	}
	
	if(axe == AXE_Z){
			decalageAxeZ = serpent->rayon*(TAILLE-1);
	        for(i=1;i<TAILLE;i++){
	            tmp = creer_point(getX(tete),getY(tete),getZ(tete)-decalageAxeZ);
		        serpent->corps = enfile(serpent->corps,tmp);
		        decalageAxeZ -= serpent->rayon;
	        }
	}
    
    serpent->corps = enfile(serpent->corps,tete);
    
	return serpent;
}


int deplacerSnake(snake* serpent, char direction){
    point* nouvelle_tete, *tete;
    
    // premiere etape: regarde s'il faut changer l'axe de deplacement suivant la direction choisi
    if (direction == 'd')
         serpent->axe = serpent->directions[serpent->type_face][serpent->axe];
    else if (direction == 'g')
         serpent->axe = axe_inverse(serpent->directions[serpent->type_face][serpent->axe]);

    // deuxieme etape: effectue le deplacement avec enfile et defile
    //fprintf(stderr, "direction: %f %f %f\n", getX(serpent->axes[serpent->axe]), getY(serpent->axes[serpent->axe]), getZ(serpent->axes[serpent->axe]));
    nouvelle_tete = defile(serpent->corps);  // recupere la fin du corps du serpent
    tete = dernier_file(serpent->corps);  // recupere la tete: sert de reference pour la nouvelle position
    //fprintf(stderr, "position tete: %f %f %f\n", getX(tete), getY(tete), getZ(tete));
    //fprintf(stderr, "position nouvelle tete: %f %f %f\n", getX(tete)+serpent->vitesse* getX(serpent->axes[serpent->axe]), getY(tete) + serpent->vitesse * getY(serpent->axes[serpent->axe]), getZ(tete) + serpent->vitesse * getZ(serpent->axes[serpent->axe]));
    setX(nouvelle_tete, getX(tete) + serpent->vitesse * getX(serpent->axes[serpent->axe]));  // deplace la composante suivant les composants de la tete, l'axe de deplacement et la vitesse
    setY(nouvelle_tete, getY(tete) + serpent->vitesse * getY(serpent->axes[serpent->axe]));
    setZ(nouvelle_tete, getZ(tete) + serpent->vitesse * getZ(serpent->axes[serpent->axe]));
    
         
    // troisieme etape: regarde s'il y a collision avec un mur
    
    // corrige la position en fonction de la collision 

    
    // quatrieme etape: regarde s'il y a collision avec lui-meme
    if (collision_serpent(serpent->corps, nouvelle_tete, serpent->rayon)){
        // affiche game over et propose de quitter?: renvoie resultat et change variable globale
        exit(0);
    }
    
    // cinquieme etape: collision avec un element de la piece


    // on finit en enfilant la nouvelle tete
    serpent->corps = enfile(serpent->corps, nouvelle_tete);
    
    return 1;
}


int collision_serpent(file corps, point* tete, int rayon){
     float d, x, y, z;
     int c = 0;
     struct_cellule* parti = corps->debut_file; // prends la deuxieme boule
     
     //fprintf(stderr, "Tete X %f Y %f Z %f\n", getX(tete), getY(tete), getZ(tete));
     while (parti->suivant != NULL){
         //fprintf(stderr, "X %f Y %f Z %f\n", getX(parti->objet), getY(parti->objet), getZ(parti->objet));
         x = getX(parti->objet) - getX(tete); y = getY(parti->objet) - getY(tete); z = getZ(parti->objet) - getZ(tete);
         d = sqrt(x*x+y*y+z*z);
         //fprintf(stderr, "Rayon %d: %f %d\n", c, d, 2*rayon);
         if (d < rayon)
             return 1;
         parti = parti->suivant;
         c ++;
     }

     return 0;
}


void afficherFace(point* a, point* b, point* c, point* d){
	/*fprintf(stderr,"A %f %f %f\n",getX(A),getY(A),getZ(A));
	fprintf(stderr,"B %f %f %f\n",getX(B),getY(B),getZ(B));
	fprintf(stderr,"C %f %f %f\n",getX(C),getY(C),getZ(C));
	fprintf(stderr,"D %f %f %f\n",getX(D),getY(D),getZ(D));*/
    glBegin(GL_QUADS);

    // jaune
	glColor3f(0.9, 0, 0);
	glVertex3f(getX(a), getY(a), getZ(a));
	glVertex3f(getX(b), getY(b), getZ(b));
    glVertex3f(getX(c), getY(c), getZ(c));
	glVertex3f(getX(d), getY(d), getZ(d));
	
	glEnd();

}


void afficherSphere(int rayon, point* position, float pas){
	float deltaO = (2*PI)/(float)pas;
	float deltaL = deltaO;
	float teta,phy;
	
	for(teta =0; teta < 2*PI ; teta+=deltaO){
		for(phy = 0 ; phy < PI/2 ; phy+=deltaL){
			afficherFace(creer_point_angle_pos(teta,phy,rayon,position),
					  creer_point_angle_pos(teta+deltaO,phy,rayon,position),
					  creer_point_angle_pos(teta+deltaO,phy+deltaL,rayon,position),
					  creer_point_angle_pos(teta,phy+deltaL,rayon,position));
			
			
			afficherFace(creer_point_angle_pos(teta,-phy,rayon,position),
					  creer_point_angle_pos(teta+deltaO,-phy,rayon,position),
					  creer_point_angle_pos(teta+deltaO,-phy-deltaL,rayon,position),
					  creer_point_angle_pos(teta,-phy-deltaL,rayon,position));
		
		}
	}
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


void afficherSnake(snake* serpent){
    struct_cellule* iterateur = serpent->corps->debut_file;
        
    while(iterateur != NULL){
        afficherSphere(serpent->rayon, iterateur->objet, 20);
        iterateur = iterateur->suivant;
    }
}


void init_directions(int directions[3][6]){
    directions[SOL][AXE_X] = AXE_Y_BIS;
    directions[SOL][AXE_X_BIS] = AXE_Y;
    directions[SOL][AXE_Y] = AXE_X;
    directions[SOL][AXE_Y_BIS] = AXE_X_BIS;
    directions[SOL][AXE_Z] = VIDE;
    directions[SOL][AXE_Z_BIS] = VIDE;
    
    directions[MUR_LATERAL][AXE_X] = VIDE;
    directions[MUR_LATERAL][AXE_X_BIS] = VIDE;
    directions[MUR_LATERAL][AXE_Y] = AXE_Z_BIS;
    directions[MUR_LATERAL][AXE_Y_BIS] = AXE_Z;
    directions[MUR_LATERAL][AXE_Z] = AXE_Y;
    directions[MUR_LATERAL][AXE_Z_BIS] = AXE_Y_BIS;
    
    directions[MUR_PER][AXE_X] = AXE_Z_BIS;
    directions[MUR_PER][AXE_X_BIS] = AXE_Z;
    directions[MUR_PER][AXE_Y] = VIDE;
    directions[MUR_PER][AXE_Y_BIS] = VIDE;
    directions[MUR_PER][AXE_Z] = AXE_X;
    directions[MUR_PER][AXE_Z_BIS] = AXE_X_BIS;
}

void init_redirection(int redirection[6][3]){
    redirection[SOL][SOL] = VIDE;
    redirection[MUR_G][SOL] = AXE_X;
    redirection[MUR_A][SOL] = AXE_Y;
    redirection[PLAFOND][SOL] = VIDE;
    redirection[MUR_D][SOL] = AXE_X_BIS;
    redirection[MUR_AR][SOL] = AXE_Y_BIS;
    
    redirection[SOL][MUR_LATERAL] = AXE_Z;
    redirection[MUR_G][MUR_LATERAL] = VIDE;
    redirection[MUR_A][MUR_LATERAL] = AXE_Y;
    redirection[PLAFOND][MUR_LATERAL] = AXE_Z_BIS;
    redirection[MUR_D][MUR_LATERAL] = VIDE;
    redirection[MUR_AR][MUR_LATERAL] = AXE_Y_BIS;
    
    redirection[SOL][MUR_PER] = AXE_Z;
    redirection[MUR_G][MUR_PER] = AXE_X;
    redirection[MUR_A][MUR_PER] = VIDE;
    redirection[PLAFOND][MUR_PER] = AXE_Z_BIS;
    redirection[MUR_D][MUR_PER] = AXE_X_BIS;
    redirection[MUR_AR][MUR_PER] = VIDE;
}

void init_axes(point* axes[6]){
    axes[AXE_X] = creer_point(1, 0, 0);  // axe des x positifs: 1,0,0
    axes[AXE_X_BIS] = creer_point(-1, 0, 0);  // axe des x negatifs: -1,0,0
    axes[AXE_Y] = creer_point(0, 1, 0);  // axe des y positifs: 0,1,0
    axes[AXE_Y_BIS] = creer_point(0, -1, 0);  // axe des y negatifs: 0,-1,0
    axes[AXE_Z] = creer_point(0, 0, 1);  // axe des z positifs: 0,0,1
    axes[AXE_Z_BIS] = creer_point(0, 0, -1);  // axe des z negatifs: 0,0,-1
}


int axe_inverse(int axe){

    switch (axe){
        case AXE_X:
            return AXE_X_BIS;
        case AXE_X_BIS:
            return AXE_X;
        case AXE_Y:
            return AXE_Y_BIS;
        case AXE_Y_BIS:
            return AXE_Y;
        case AXE_Z:
            return AXE_Z_BIS;
        case AXE_Z_BIS:
            return AXE_Z;
        default:
            return AXE_X;
    }

}




