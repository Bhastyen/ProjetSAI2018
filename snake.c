#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "GL/gl.h"
#include "GL/glut.h"

#include "snake.h"
#include "define.h"
#define PI 3.14156


int axe_inverse(int axe);
int mur_oppose(int mur);
int type_face(int face);
void corrige_position(point* nouvelle_tete, int correction[2], snake* serpent);
void init_redirection(int redirection[6][3]);
void init_directions(int directions[6][6]);
void init_transition(int transition[3][6]);
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
    init_transition(serpent->transition);
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


int deplacerSnake(snake* serpent, para* p, char direction){
    point* nouvelle_tete, *tete;
    int correction[2] = {0, 0};
    
    // premiere etape: regarde s'il faut changer l'axe de deplacement suivant la direction choisi
    if (direction == 'd')
         serpent->axe = serpent->directions[serpent->face][serpent->axe];
    else if (direction == 'g')
         serpent->axe = axe_inverse(serpent->directions[serpent->face][serpent->axe]);

    // deuxieme etape: effectue le deplacement avec enfile et defile
    //fprintf(stderr, "direction: %f %f %f\n", getX(serpent->axes[serpent->axe]), getY(serpent->axes[serpent->axe]), getZ(serpent->axes[serpent->axe]));
    nouvelle_tete = defile(serpent->corps);  // recupere la fin du corps du serpent
    tete = dernier_file(serpent->corps);  // recupere la tete: sert de reference pour la nouvelle position
    //fprintf(stderr, "position tete: %f %f %f\n", getX(tete), getY(tete), getZ(tete));
    //fprintf(stderr, "position nouvelle tete: %f %f %f\n", getX(tete)+serpent->vitesse* getX(serpent->axes[serpent->axe]), getY(tete) + serpent->vitesse * getY(serpent->axes[serpent->axe]), getZ(tete) + serpent->vitesse * getZ(serpent->axes[serpent->axe]));
    setX(nouvelle_tete, getX(tete) + serpent->vitesse * getX(serpent->axes[serpent->axe]));  // deplace la composante suivant les composants de la tete, l'axe de deplacement et la vitesse
    setY(nouvelle_tete, getY(tete) + serpent->vitesse * getY(serpent->axes[serpent->axe]));
    setZ(nouvelle_tete, getZ(tete) + serpent->vitesse * getZ(serpent->axes[serpent->axe]));
    
    
    // troisieme etape: regarde s'il y a collision avec lui-meme
    if (collision_serpent(serpent->corps, nouvelle_tete, serpent->rayon)){
        // affiche game over et propose de quitter: renvoie resultat et change variable globale
        return GAME_OVER;
    }
         
    // quatrieme etape: regarde s'il y a collision avec un mur
    if (collision_mur(nouvelle_tete, p, serpent->rayon, correction, serpent->face) == 1){
        //fprintf(stderr, "axe = %d correction = %d\n", correction[0], correction[1]);
        //if (correction[1] == VIDE)  // j ai traverse un mur vide: changement de piece
            // serpent->piece = changement_piece(p, pieces, nouvelle_tete, serpent->piece, correction[0]);
            // collision avec le sol
            //if (collision_sol(nouvelle_tete, p, serpent->rayon, correction, serpent->face) == 0){
                 // corrige_position_sol(nouvelle_tete, serpent);
            //}
        /*else */corrige_position(nouvelle_tete, correction, serpent);  // corrige la position en fonction de la collision
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


int collision_mur(point* tete, para* p, int rayon, int correction[2], int face_exeption){  // verifie la collision avec chaque mur
    
    if (getY(tete)-rayon <= getY(p->pos) && face_exeption != MUR_A){   // mur de devant
         //fprintf(stderr, "point -y serpent = %f  -y face = %f\n", getY(tete)-rayon, getY(p->pos));
         //if (pieces[MUR_A] == VIDE){
             // correction[0] = AXE_Y_BIS;
             // correction[1] = VIDE;
             //return 1;
         //}
         correction[0] = AXE_Y_BIS;
         correction[1] = getY(p->pos) - (getY(tete) - rayon);  // permettra la bonne correction
         return 1;
    }
    
    if (getY(tete)+rayon >= getY(p->pos)+getY(p->t_aretes) && face_exeption != MUR_AR){   // mur du fond
         //fprintf(stderr, "point y serpent = %f  y face = %f\n", getY(tete)+rayon, getY(p->pos)+getY(p->t_aretes));
         correction[0] = AXE_Y;
         correction[1] = (getY(tete) + rayon) - (getY(p->pos) + getY(p->t_aretes));  // permettra la bonne correction
         return 1;
    }
    
    if (getX(tete)-rayon <= getX(p->pos) && face_exeption != MUR_G){    // mur de gauche
         //fprintf(stderr, "point -x serpent = %f  -x face = %f\n", getX(tete)-rayon, getX(p->pos));
         correction[0] = AXE_X_BIS;
         correction[1] = getX(p->pos) - (getX(tete) - rayon);  // permettra la bonne correction
         return 1;
    }
         
    if (getX(tete)+rayon >= getX(p->pos)+getX(p->t_aretes) && face_exeption != MUR_D){    // mur de droite
         //fprintf(stderr, "point x serpent = %f  x face = %f\n", getX(tete)+rayon, getX(p->pos)+getX(p->t_aretes));
         correction[0] = AXE_X;
         correction[1] = (getX(tete) + rayon) - (getX(p->pos)+getX(p->t_aretes));  // permettra la bonne correction
         return 1;
    }
    
    if (getZ(tete)-rayon <= getZ(p->pos) && face_exeption != SOL){    // sol
         //fprintf(stderr, "point -z serpent = %f  -z face = %f\n", getZ(tete)-rayon, getZ(p->pos));
         correction[0] = AXE_Z_BIS;
         correction[1] = getZ(p->pos) - (getZ(tete) - rayon);  // permettra la bonne correction
         return 1;
    }
    
    if (getZ(tete)+rayon >= getZ(p->pos)+getZ(p->t_aretes) && face_exeption != PLAFOND){   // plafond
         //fprintf(stderr, "point z serpent = %f  z face = %f\n", getZ(tete)+rayon, getZ(p->pos)+getZ(p->t_aretes));
         correction[0] = AXE_Z;
         correction[1] = (getZ(tete) + rayon) - (getZ(p->pos) + getZ(p->t_aretes));  // permettra la bonne correction
         return 1;
    }
    
    return 0;
}


int collision_sol(point* tete, para* p, int rayon, int face_sol){  // verifie la collision avec le sol actuelle du serpent
 
    if (getY(tete)-rayon <= getY(p->pos) && face_sol == MUR_A)   // mur de devant 
        return 1;
    
    if (getY(tete)+rayon >= getY(p->pos)+getY(p->t_aretes) && face_sol == MUR_AR)   // mur du fond
        return 1;
    
    if (getX(tete)-rayon <= getX(p->pos) && face_sol == MUR_G)    // mur de gauche
         return 1;
         
    if (getX(tete)+rayon >= getX(p->pos)+getX(p->t_aretes) && face_sol == MUR_D)    // mur de droite
         return 1;
    
    if (getZ(tete)-rayon <= getZ(p->pos) && face_sol == SOL)    // sol
         return 1;
    
    if (getZ(tete)+rayon >= getZ(p->pos)+getZ(p->t_aretes) && face_sol == PLAFOND)   // plafond
         return 1;
    
    return 0;
}


void corrige_position(point* nouvelle_tete, int correction[2], snake* serpent){
     int ex_face;
     
     // recupere la nouvelle face
     ex_face = serpent->face; 
     serpent->face = serpent->transition[serpent->type_face][correction[0]];
     serpent->type_face = type_face(serpent->face);
     
     // correction: 'recule' la tete pour qu'il n'y ait plus de collision
     setX(nouvelle_tete, getX(nouvelle_tete) + correction[1] * getX(serpent->axes[axe_inverse(correction[0])]));  // replace le serpent 
     setY(nouvelle_tete, getY(nouvelle_tete) + correction[1] * getY(serpent->axes[axe_inverse(correction[0])]));
     setZ(nouvelle_tete, getZ(nouvelle_tete) + correction[1] * getZ(serpent->axes[axe_inverse(correction[0])]));
    
     // recherche le nouvel axe de deplacement
     serpent->axe = serpent->redirection[ex_face][serpent->type_face];
     
     // deplacement au bonne endroit cette fois
     setX(nouvelle_tete, getX(nouvelle_tete) + serpent->vitesse * getX(serpent->axes[serpent->axe]));  // bouge le serpent dans la bonne direction
     setY(nouvelle_tete, getY(nouvelle_tete) + serpent->vitesse * getY(serpent->axes[serpent->axe]));
     setZ(nouvelle_tete, getZ(nouvelle_tete) + serpent->vitesse * getZ(serpent->axes[serpent->axe]));
     
}


void corrige_position_sol(point* nouvelle_tete, snake* serpent){
     int ex_face;
     
     // recupere la nouvelle face
     ex_face = serpent->face; 
     serpent->face = mur_oppose(serpent->transition[serpent->type_face][serpent->axe]);
     serpent->type_face = type_face(serpent->face);
     
     // recherche le nouvel axe de deplacement
     serpent->axe = axe_inverse(serpent->redirection[ex_face][serpent->type_face]);
     
     // deplacement au bonne endroit cette fois
     setX(nouvelle_tete, getX(nouvelle_tete) + serpent->vitesse * getX(serpent->axes[serpent->axe]));  // bouge le serpent dans la bonne direction
     setY(nouvelle_tete, getY(nouvelle_tete) + serpent->vitesse * getY(serpent->axes[serpent->axe]));
     setZ(nouvelle_tete, getZ(nouvelle_tete) + serpent->vitesse * getZ(serpent->axes[serpent->axe]));
     
}


/*void changement_piece(para* p, point* nouvelle_tete, int piece){
    
    
    if ()

}*/


void afficherFace(point* a, point* b, point* c, point* d){
	/*fprintf(stderr,"A %f %f %f\n",getX(A),getY(A),getZ(A));
	fprintf(stderr,"B %f %f %f\n",getX(B),getY(B),getZ(B));
	fprintf(stderr,"C %f %f %f\n",getX(C),getY(C),getZ(C));
	fprintf(stderr,"D %f %f %f\n",getX(D),getY(D),getZ(D));*/
    glBegin(GL_QUADS);

    // jaune
	glColor3f(0.9, 0.5, 0);
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


void init_directions(int directions[6][6]){
    directions[SOL][AXE_X] = AXE_Y_BIS;
    directions[SOL][AXE_X_BIS] = AXE_Y;
    directions[SOL][AXE_Y] = AXE_X;
    directions[SOL][AXE_Y_BIS] = AXE_X_BIS;
    directions[SOL][AXE_Z] = VIDE;
    directions[SOL][AXE_Z_BIS] = VIDE;
    
    directions[PLAFOND][AXE_X] = AXE_Y;
    directions[PLAFOND][AXE_X_BIS] = AXE_Y_BIS;
    directions[PLAFOND][AXE_Y] = AXE_X_BIS;
    directions[PLAFOND][AXE_Y_BIS] = AXE_X;
    directions[PLAFOND][AXE_Z] = VIDE;
    directions[PLAFOND][AXE_Z_BIS] = VIDE;
    
    directions[MUR_G][AXE_X] = VIDE;
    directions[MUR_G][AXE_X_BIS] = VIDE;
    directions[MUR_G][AXE_Y] = AXE_Z_BIS;
    directions[MUR_G][AXE_Y_BIS] = AXE_Z;
    directions[MUR_G][AXE_Z] = AXE_Y;
    directions[MUR_G][AXE_Z_BIS] = AXE_Y_BIS;
    
    directions[MUR_D][AXE_X] = VIDE;
    directions[MUR_D][AXE_X_BIS] = VIDE;
    directions[MUR_D][AXE_Y] = AXE_Z;
    directions[MUR_D][AXE_Y_BIS] = AXE_Z_BIS;
    directions[MUR_D][AXE_Z] = AXE_Y_BIS;
    directions[MUR_D][AXE_Z_BIS] = AXE_Y;
    
    directions[MUR_A][AXE_X] = AXE_Z;
    directions[MUR_A][AXE_X_BIS] = AXE_Z_BIS;
    directions[MUR_A][AXE_Y] = VIDE;
    directions[MUR_A][AXE_Y_BIS] = VIDE;
    directions[MUR_A][AXE_Z] = AXE_X_BIS;
    directions[MUR_A][AXE_Z_BIS] = AXE_X;
    
    directions[MUR_AR][AXE_X] = AXE_Z_BIS;
    directions[MUR_AR][AXE_X_BIS] = AXE_Z;
    directions[MUR_AR][AXE_Y] = VIDE;
    directions[MUR_AR][AXE_Y_BIS] = VIDE;
    directions[MUR_AR][AXE_Z] = AXE_X;
    directions[MUR_AR][AXE_Z_BIS] = AXE_X_BIS;
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

void init_transition(int transition[3][6]){
    
    transition[SOL][AXE_X] = MUR_D;
    transition[SOL][AXE_X_BIS] = MUR_G;
    transition[SOL][AXE_Y] = MUR_AR;
    transition[SOL][AXE_Y_BIS] = MUR_A;
    transition[SOL][AXE_Z] = VIDE;
    transition[SOL][AXE_Z_BIS] = VIDE;
    
    transition[MUR_LATERAL][AXE_X] = VIDE;
    transition[MUR_LATERAL][AXE_X_BIS] = VIDE;
    transition[MUR_LATERAL][AXE_Y] = MUR_AR;
    transition[MUR_LATERAL][AXE_Y_BIS] = MUR_A;
    transition[MUR_LATERAL][AXE_Z] = PLAFOND;
    transition[MUR_LATERAL][AXE_Z_BIS] = SOL;
    
    transition[MUR_PER][AXE_X] = MUR_D;
    transition[MUR_PER][AXE_X_BIS] = MUR_G;
    transition[MUR_PER][AXE_Y] = VIDE;
    transition[MUR_PER][AXE_Y_BIS] = VIDE;
    transition[MUR_PER][AXE_Z] = PLAFOND;
    transition[MUR_PER][AXE_Z_BIS] = SOL;
    
}

int axe_inverse(int axe){   // permet de recuperer la valeur de l'axe inverse

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

int mur_oppose(int mur){   // permet de recuperer la valeur du mur oppose

    switch (mur){
        case MUR_A:
            return MUR_AR;
        case MUR_AR:
            return MUR_A;
        case MUR_D:
            return MUR_G;
        case MUR_G:
            return MUR_D;
        case SOL:
            return PLAFOND;
        case PLAFOND:
            return SOL;
        default:
            return SOL;
    }

}


int type_face(int face){   // permet de savoir a partir d'une face le type de face associe
    
    if (face == SOL || face == PLAFOND)
        return SOL;
    if (face == MUR_G || face == MUR_D)
        return MUR_LATERAL;
    if (face == MUR_A || face == MUR_AR)
        return MUR_PER;
     
    return SOL;
}

