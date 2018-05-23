#include <stdio.h>
#include <stdlib.h>
#include "labyrinthe.h"
#include "GL/gl.h"
#include "GL/glut.h"
#include "math.h"
#include <time.h>

void initilisation_type_piece(piece liste_pieces[63]){
  int k;
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

  int w=0;

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
/*
  typedef struct {
  point* pos_bg; //position bas "gauche" de la piece
  int taille;
  int type_piece;
  int adjacent[6];
  } piece_laby;

*/

void creer_labyrinthe(piece_laby liste_pieces[LARGEUR*HAUTEUR*PROFONDEUR]){
  int laby[LARGEUR][HAUTEUR][PROFONDEUR];//matrice de passage
  int longueur_chemin;
  element indice_depart;
  element indice_piece_en_cours;
  indice_depart.indice = 0;
  piece liste_types_pieces[63];
  initilisation_type_piece(liste_types_pieces);
  piece_laby piece_en_cours;
  file candidats = creer_file_vide();// candidats a la creation du labyrinthe, vont se "choisir" par rapport a l'adjacence
	

	
	
	
  initilisation_labyrinthe(laby);
  //initilisation_premiere_piece(listes_pieces[0],liste_pieces);
  candidats=enfile(candidats,indice_depart);
  liste_pieces[0].longueur_chemin = 0;
  while (!file_est_vide(candidats) && (longueur_chemin < NOMBRE_PIECE)){
	
    indice_piece_en_cours = defile(candidats);
    piece_en_cours =  liste_pieces[indice_piece_en_cours.indice];
		
    longueur_chemin=adjacence_piece(piece_en_cours,
				    indice_piece_en_cours.indice,
				    liste_pieces,
				    liste_types_pieces,
				    laby,
				    candidats);
  }
}

int adjacence_piece(piece_laby piece_courante,
		    int indice,
		    piece_laby liste_piece[LARGEUR*HAUTEUR*PROFONDEUR],
		    piece liste_types_pieces[63],
		    int laby[LARGEUR][HAUTEUR][PROFONDEUR],
		    file candidats){
					
  int w,i,k,j,i_tmp,k_tmp,j_tmp,ok=0;
  element indice_adjacent;  
  calcul_position_point(indice,piece_courante.pos_bg);
  piece_courante.taille = 1;
  srand(time(NULL));
  piece_courante.type_piece = (rand ()%(60-7+1))+7;
  
  determine_i_k_j(indice,&i,&k,&j);//On obtient les indice i,j,k dans matrice LxHxP , va permettre de déduire la position des cotés adjacents
  fprintf(stderr," dans adjacence piece\n");
  for(w=0;w<6;i++){//Pour chaque face de la piece
    if(liste_types_pieces[piece_courante.type_piece].murs[w] == 0){// cas ou il n'y a pas de murs 
      i_tmp = i;	
      k_tmp = k;
      j_tmp =j;
      ok = 0 ;
      switch(w){
      case 0:
	if (k >0){
	  k_tmp--;
	  ok = 1;
	}
  			 	
	break;
      case 1:	
	if (j >0){
	  j_tmp--;
	  ok = 1;
	}
	break;
      case 2:
	if( k<PROFONDEUR){
	  k_tmp++;
	  ok = 1;
	}
	break;
      case 3:
	if (j <HAUTEUR){
	  j_tmp++;
	  ok = 1;
  					
	}
	break;
      case 4:
	if(i < LARGEUR){
	  i_tmp++;
	  ok = 1;
	}
	break;
      case 5:
	if(i>0){
	  i_tmp--;
	  ok = 1;
	}
	break;
  		
  		
      }
      if(ok == 1){// Si la piece est adjacente
	indice_adjacent.indice = calcul_indice(i_tmp,k_tmp,j_tmp);
	piece_courante.murs[w] = 0;
	piece_courante.adjacent= enfile(piece_courante.adjacent,indice_adjacent);
	if(laby[i_tmp][k_tmp][j_tmp] == NON_VUE){
	  candidats = enfile(candidats,indice_adjacent);
	  laby[i_tmp][k_tmp][j_tmp] = VUE;
	  liste_piece[indice_adjacent.indice].longueur_chemin =piece_courante.longueur_chemin +1 ;
  				
	};
      }
      else{//SInon on ajout un mur si contrainte
	piece_courante.murs[w] = 1;
  		
      }
  	
    }else{
      piece_courante.murs[w] = 1;
  	
  	
    }
  
  }
  
  return piece_courante.longueur_chemin+1;
}

void determine_i_k_j(int indice,int* i,int* k,int* j){
  int tmp;
  *k= indice / (LARGEUR*HAUTEUR);
  tmp = indice -(LARGEUR*HAUTEUR*(*k));
  *j = tmp / LARGEUR;
  *i = tmp - LARGEUR * (*j);

}

int calcul_indice(int i,int k,int j){
  return ((i+(LARGEUR*j))+(LARGEUR*HAUTEUR*k));
}
void calcul_position_point(int indice,point* p){
  int i,j,k; // i largeur, j hauteur,k profondeur
	

  /*Calcul point bas gauche piece*/
  determine_i_k_j(indice,&i,&k,&j);
  p=creer_point( TAILLE_PIECE*i,  TAILLE_PIECE*k, TAILLE_PIECE*j );
	

}

void afficher_labyrinthe(piece_laby liste_pieces[LARGEUR*HAUTEUR*PROFONDEUR]){
 file pieces_a_afficher = creer_file_vide();
 piece_laby piece_courante = liste_pieces[0]; // depart a redefinir
 //struct_cellule* piece_en_cours = liste_pieces.adjacent
 int i;
 for(i=0;i<HAUTEUR*LARGEUR*PROFONDEUR;i++){
   // visualiser_piece_laby(piece_courante);
   visualiser_piece_laby(liste_pieces[i]); // test qui va sureme,nt cracher


 }

}

void visualiser_piece_laby(piece_laby  p){// different de afficher piece laby
	
  int x1=(int)getX(p.pos_bg);
  int x2=x1+1*TAILLE_PIECE;
  int y1=(int)getY(p.pos_bg);
  int y2=y1+TAILLE_PIECE;
  int z1=(int)getZ(p.pos_bg);
  int z2=z1+TAILLE_PIECE;
	
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

