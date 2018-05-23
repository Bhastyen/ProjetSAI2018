#include <stdio.h>
#include <stdlib.h>
#include "labyrinthe.h"
#include "GL/gl.h"
#include "GL/glut.h"

void initilisation_type_piece(piece liste_pieces[63]){
 int i,j,k;
 //TODO algo :  nombre 1 avant , quand trouver ajouter 1 au suivant , tant que < 6
 
 
 
 /*0 parmi 6 = 1 combinaison */
 for(k=0;k<6;k++){
 
 liste_pieces[0].murs[k] =0;
 }
 
 
 /*1 parmi 6 = 6 combinaisons*/
 init_type_pieces_bis(liste_pieces ,1,0,1,6);
 //init_type_pieces_bis(piece liste_pieces[63] ,int nombre_murs,int indice_depart,int indice_depart_nouveau ,int nombre_combinaisons)
 /*
 liste_pieces[1].murs ={1,0,0,0,0,0};
 liste_pieces[2].murs ={0,1,0,0,0,0};
 liste_pieces[3].murs ={0,0,1,0,0,0};
 liste_pieces[4].murs ={0,0,0,1,0,0};
 liste_pieces[5].murs ={0,0,0,0,1,0};
 liste_pieces[6].murs ={0,0,0,0,0,1};
 */
  
 /*2 parmi 6 = 15 combinaisons*/
 init_type_pieces_bis(liste_pieces ,2,1,7,15);

 
  /*3 parmi 6 = 20 combinaisons*/
  init_type_pieces_bis(liste_pieces ,3,7,22,20);
  
   
  /*4 parmi 6 = 15 combinaisons*/
  init_type_pieces_bis(liste_pieces ,4,22,42,15);
  
   
  /*5 parmi 6 = 6 combinaisons*/
  init_type_pieces_bis(liste_pieces ,5,42,57,6);
  
  
   afficher_result(liste_pieces);
  /*
 liste_pieces[7].murs ={1,1,0,0,0,0};
 liste_pieces[8].murs ={1,0,1,0,0,0};
 liste_pieces[9].murs ={1,0,0,1,0,0};
 liste_pieces[10].murs ={1,0,0,0,1,0};
 liste_pieces[11].murs ={1,0,0,0,0,1};
 
 liste_pieces[12].murs ={0,1,1,0,0,0};
 liste_pieces[13].murs ={0,1,0,1,0,0};
 liste_pieces[14].murs ={0,1,0,0,1,0};
 liste_pieces[15].murs ={0,1,0,0,0,1};   
 
 liste_pieces[16].murs ={0,0,1,1,0,0};
 liste_pieces[17].murs ={0,0,1,0,1,0};
 liste_pieces[18].murs ={0,0,1,0,0,1};
 
 liste_pieces[19].murs ={0,0,0,1,1,0};
 liste_pieces[20].murs ={0,0,0,1,0,1};
   
 liste_pieces[21].murs ={0,0,0,0,1,1};*/

  /*3 parmi 6 = 20 combinaisons*/
 /*
 liste_pieces[22].murs ={1,1,1,0,0,0};
 liste_pieces[23].murs ={1,1,0,1,0,0};
 liste_pieces[24].murs ={1,1,0,0,1,0};
 liste_pieces[25].murs ={1,1,0,0,0,1};
 
 liste_pieces[26].murs ={1,0,1,1,0,0};
 liste_pieces[27].murs ={1,0,1,0,1,0};
 liste_pieces[28].murs ={1,0,1,0,0,1};
 
 
 liste_pieces[29].murs ={1,0,0,1,1,0};
 liste_pieces[30].murs ={1,0,0,1,0,1};
 
 liste_pieces[31].murs ={1,0,0,0,1,1};
 
 liste_pieces[32].murs ={0,1,1,1,0,0};
 liste_pieces[33].murs ={0,1,1,0,1,0};
 liste_pieces[34].murs ={0,1,1,0,0,1};
 
 liste_pieces[35].murs ={0,1,0,1,1,0};
 liste_pieces[36].murs ={0,1,0,1,0,1};
 
 liste_pieces[37].murs ={0,1,0,0,1,1}; 
 
 liste_pieces[38].murs ={0,0,1,1,1,0};
 liste_pieces[39].murs ={0,0,1,1,0,1};
  
 liste_pieces[40].murs ={0,0,1,0,1,1};
 
 liste_pieces[41].murs ={0,0,0,1,1,1};
 */
   /*4 parmi 6 = 15 combinaisons*/
 /*
 liste_pieces[42].murs ={1,1,1,1,0,0};
 liste_pieces[43].murs ={1,1,1,0,1,0};
 liste_pieces[44].murs ={1,1,1,0,0,1};
 
 liste_pieces[45].murs ={1,1,0,1,1,0};
 liste_pieces[46].murs ={1,1,0,1,0,1};
 
 liste_pieces[47].murs ={1,1,0,0,1,1};
 
 liste_pieces[48].murs ={1,0,1,1,1,0};
 liste_pieces[49].murs ={1,0,1,1,0,1};
  
 liste_pieces[50].murs ={1,0,1,0,1,1};
 
 liste_pieces[51].murs ={1,0,0,1,1,1};
 
 liste_pieces[52].murs ={0,1,1,1,1,0};
 liste_pieces[53].murs ={0,1,1,1,0,1};
 
 liste_pieces[54].murs ={0,1,1,0,1,1};

 liste_pieces[55].murs ={0,1,0,1,1,1};
 
 liste_pieces[56].murs ={0,0,1,1,1,1};
*/
  /*5 parmi 6 = 6 combinaisons*/
 /*
 liste_pieces[57].murs ={1,1,1,1,1,0};
 liste_pieces[58].murs ={1,1,1,1,0,1}
 
 liste_pieces[59].murs ={1,1,1,0,1,1};
 
 liste_pieces[60].murs ={1,1,0,1,1,1};
 
 liste_pieces[61].murs ={1,0,1,1,1,1};
 
 liste_pieces[62].murs ={0,1,1,1,1,1};
*/
}

void init_type_pieces_bis(piece liste_pieces[63] ,int nombre_murs,int indice_depart,int indice_depart_nouveau ,int nombre_combinaisons){/*Fonction pas fini*/

 int i=indice_depart;
 int j=indice_depart_nouveau;//indice_nouvelle piece
 int k=0;// indice murs
 int nombre_un=0; //nombre de murs trouver
 int pos; // pos trouver de decalage
 int indice_fixe;
 int w=0;
 int z=0;
 while(i<=indice_depart+nombre_combinaisons-1){
 	k=0;

 	for(k=0;k<6;k++){
 
	 	if(liste_pieces[i].murs[k]==1){
	 		nombre_un++;
	 	}
	 	if(nombre_un== nombre_murs-1){//quand on a atteint le nombre de murs voulu -1 
	 		pos = k; // on garde la positition ou on va commencenr a ajouter un un en decalant a chaque nouvelle piece
	 	
	 		while(pos<5){
	 			w=0;
	
	 			while(w<=pos){//On recopie le morceau avant la position
	 				liste_pieces[j].murs[w] = liste_pieces[i].murs[w];
	 				w++;
	 			}
	 			
	 				if(nombre_murs == 1 ){
		 				liste_pieces[j].murs[pos] = 1;
		 				w = pos+1;
		 				
		 				
		 				while(w<6){// on remet des zero
		 					liste_pieces[j].murs[w]=0;
		 					w++;
		 				}
		 				if(pos == 4){//cas particulier
		 					pos = 5;
		 					j++;
		 					while(w<=pos){//On recopie le morceau avant la position
		 						liste_pieces[j].murs[w] = liste_pieces[i].murs[w];
		 						w++;
	 						}
		 					liste_pieces[j].murs[pos] = 1;
		 					w = pos+1;
		 				}
	 				}
	 				else{	
	 					liste_pieces[j].murs[pos+1] = 1;
		 				w = pos+2;
		 				
		 				while(w<6){// on remet des zero
		 					liste_pieces[j].murs[w]=0;
		 					w++;
		 				}
	 				
	 				}	 				
	 			
	 			pos++;
	 			j++;
	 				
	 		}
	 
	 		
	 		nombre_un = 0;
 			
 			k=6;
	 	}
	 	
 	}
 	i++;
	
 }

}

void afficher_result(piece liste_pieces[63]){
	int k;
	int i=0;
	while(i<63){
		fprintf(stderr,"{");
		for(k=0;k<6;k++){
			fprintf(stderr , "%d, ",liste_pieces[i].murs[k]);
		}
		fprintf(stderr,"}\n");
		i++;
	}

}
 
 
void visualiser_type_piece(piece  p){// different de afficher piece laby
	
	int x1=0,x2=TAILLE_PIECE,y1=0,y2=TAILLE_PIECE,z1=0,z2=TAILLE_PIECE;
	
    glBegin(GL_QUADS);
	//cyan
	
	if(p.murs[0]==1){
	    glColor3f(0, 0.9, 0.9);
		glVertex3f(x1, y1, z2);
		glVertex3f(x1, y1, z1);
		glVertex3f(x2, y1, z1);
		glVertex3f(x2, y1, z2);
		
	}	
    // jaune
    
    if(p.murs[1]==1){
		glColor3f(0.9, 0.9, 0);
		glVertex3f(x1, y1, z1);
		glVertex3f(x2, y1, z1);
		glVertex3f(x2, y2, z1);
		glVertex3f(x1, y2, z1);
	}
      
      //rouge
    if(p.murs[2]==1){
		
		glColor3f(0.9, 0, 0);
		glVertex3f(x1, y2, z2);
		glVertex3f(x2, y2, z2);
		glVertex3f(x2, y2, z1);
		glVertex3f(x1, y2, z1);
	}
	// bleu 0
    if(p.murs[3]==1){
    	glColor3f(0, 0, 0.9);
		glVertex3f(x1, y1, z2);
		glVertex3f(x1, y2, z2);
		glVertex3f(x2, y2, z2);
		glVertex3f(x2, y1, z2);
	}
		
	// rose
    if(p.murs[4]==1){
    glColor3f(0.9, 0, 0.9);
		glVertex3f(x2, y1, z2);
		glVertex3f(x2, y2 ,z2);
		glVertex3f(x2, y2, z1);
		glVertex3f(x2, y1, z1);
		
	}
	//vert
    if(p.murs[5]==1){
        glColor3f(0, 0.9, 0);
		glVertex3f(x1, y1, z2);
		glVertex3f(x1, y2, z2);
		glVertex3f(x1, y2, z1);
		glVertex3f(x1, y1, z1);

		
	}
	glEnd();

}
 
void initilisation_labyrinthe(int laby[LARGEUR][HAUTEUR][PROFONDEUR]){
	int i,j,k;
	
	for(i=0;i<LARGEUR;i++){
		for(j=0;j<HAUTEUR;j++){
			for(k=0;k<PROFONDEUR;k++){
				laby[i][j][k]=-1;
			}
		}
	}
}

void creer_labyrinthe(){
	int laby[LARGEUR][HAUTEUR][PROFONDEUR];
	int xD,yD,zD=0; // indice depart
	int xA=5,5,5; // indices arrivee
	
	file candidats;// candidats a la creation du labyrinthe, vont se "choisir" par rapport a l'adjacence
	
	initilisation_labyrinthe(laby);
	candidats=enfile(
	
}


