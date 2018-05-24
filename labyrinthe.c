#include <stdio.h>
#include <stdlib.h>
#include "labyrinthe.h"
#include "GL/gl.h"
#include "GL/glut.h"
#include "math.h"
#include <time.h>
#include "./module/mon_allocation.h"
#include "snake.h"


piece liste_types_pieces[63];
int indice_piece_final;
element pomme;
int accomplit = 0;

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
  int random_bonus;
  int indice_mur_bonus;
  int w=0;

  while(i<=indice_depart+nombre_combinaisons-1){
    k=0;
    liste_pieces[i].objets = creer_file_vide();
    for(k=0;k<6;k++){
 
      if(liste_pieces[i].murs[k]==1){
	nombre_un++;
      }
      if(nombre_un== nombre_murs-1){//quand on a atteint le nombre de murs voulu -1 
	pos = k; // on garde la positition ou on va commencenr a ajouter un un en decalant a chaque nouvelle piece
	 	
	while(pos<5){
	  w=0;
		liste_pieces[j].objets = creer_file_vide();
		random_bonus =(rand ()%(2-1))+1;
		indice_mur_bonus=rand ()%(5);
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
	 	if(random_bonus == 1){
	 	
    	liste_pieces[j].objets = enfile(liste_pieces[j].objets,creer_bonus(indice_mur_bonus));
    	 //pieces_a_afficher->debut_file;
    
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
  int longueur_chemin=0;
  element indice_depart;
  element indice_piece_en_cours;
  indice_depart.indice = PIECE_DEPART;

  initilisation_type_piece(liste_types_pieces);
  piece_laby piece_en_cours;
  file candidats = creer_file_vide();// candidats a la creation du labyrinthe, vont se "choisir" par rapport a l'adjacence
  srand(time(NULL));	

  int i,j,k;

	
  /*Initilise matrice HxLxP , servant a déterminer quel pieces ont déja été reconnu*/
  initilisation_labyrinthe(laby);
  //initilisation_premiere_piece(listes_pieces[0],liste_pieces);
  
  //Commencement avec la premier piese
  candidats=enfile(candidats,indice_depart);
 
  liste_pieces[PIECE_DEPART].longueur_chemin = 0;
  
  
  while ((longueur_chemin < NOMBRE_PIECE)){
  
    if(file_est_vide(candidats)){
    	candidats = enfile(candidats,indice_piece_en_cours);
    
    } 
    indice_piece_en_cours = defile(candidats); 
	
    longueur_chemin=adjacence_piece(
				    indice_piece_en_cours.indice,
				    liste_pieces,
				    liste_types_pieces,
				    laby,
				    &candidats);

				   // determine_i_k_j(indice_piece_en_cours.indice,&i,&k,&j);
				    if(longueur_chemin == NOMBRE_PIECE){
				    	indice_piece_final = indice_piece_en_cours.indice;
				    
				    }

    }
}

int adjacence_piece(
		    int indice,
		    piece_laby liste_piece[LARGEUR*HAUTEUR*PROFONDEUR],
		    piece liste_types_pieces[63],
		    int laby[LARGEUR][HAUTEUR][PROFONDEUR],
		    file* candidats){
					
  int w,i,k,j,i_tmp,k_tmp,j_tmp,ok=0;
  element indice_adjacent;  
  calcul_position_point(indice,&liste_piece[indice]);
 
  liste_piece[indice].taille = 1;

  liste_piece[indice].type_piece = (rand ()%(57-14+1))+14;
  //fprintf(stderr," dans adjacence piece\n");
  liste_piece[indice].adjacent = creer_file_vide();

  
  determine_i_k_j(indice,&i,&k,&j);//On obtient les indice i,j,k dans matrice LxHxP , va permettre de déduire la position des cotés adjacents

  for(w=0;w<6;w++){//Pour chaque face de la piece

    ok = 0 ;// cas ou il n'y a pas de murs
    
     if(liste_types_pieces[liste_piece[indice].type_piece].murs[w] == 0){
     
      i_tmp = i;	
      k_tmp = k;
      j_tmp =j;
     
      switch(w){
      case 0:
		 if (k >0){
		  k_tmp--;
		  ok = 1;
		}
  			 	
	 break;
      case 1:	
			if (j >0 && indice != PIECE_DEPART){// Pour toujorus avoir un sol pour mettre objet
			  j_tmp--;
			  ok = 1;
			}
		break;
      case 2:
			if( k<PROFONDEUR-1){
			  k_tmp++;
			  ok = 1;
			}
	break;
      case 3:
			if (j <HAUTEUR-1){
			  j_tmp++;
			  ok = 1;
  					
	}
	break;
      case 4:
			if(i < LARGEUR-1){
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
	
	  
      if(indice != PIECE_DEPART && ok ==1){// point entree
			switch(liste_piece[indice].point_entree){
			case 0:

			  liste_piece[indice].murs[2] = 0;

		  			 	
			  break;
			case 1:	
			  liste_piece[indice].murs[3] = 0;
			  break;
			case 2:
			  liste_piece[indice].murs[0] = 0;
			  break;
			case 3:
			  liste_piece[indice].murs[1] = 0;
			  break;
			case 4:
			  liste_piece[indice].murs[5] = 0;
			  break;
			case 5:
			  liste_piece[indice].murs[4] = 0;
			  break;

			}
      }
      else{
      		liste_piece[indice].murs[1] = 1;// permet d'avoir toujorus un sol pour piece de depart
      }
		  if(ok == 1){// Si la piece est adjacente
				ok = 0;
				indice_adjacent.indice = calcul_indice(i_tmp,k_tmp,j_tmp);
				liste_piece[indice].adjacent= enfile(liste_piece[indice].adjacent,indice_adjacent);

				
				
				//fprintf(stderr," dans adjacence piece OK = 1 indice_adjacent %d , indice_courant %d",indice_adjacent.indice,indice);
				if(laby[i_tmp][k_tmp][j_tmp] == NON_VUE){

				  /*initialise la position de la piece*/
				  calcul_position_point( indice_adjacent.indice,&liste_piece[indice_adjacent.indice]);
				 
				 // fprintf(stderr," NON VUE \n");
				  /*ajout nouveau candidat a traiter*/
				  *candidats = enfile(*candidats,indice_adjacent);
				  laby[i_tmp][k_tmp][j_tmp] = NON_TRAITEE;
				  liste_piece[indice_adjacent.indice].point_entree = w;
				  liste_piece[indice_adjacent.indice].longueur_chemin =liste_piece[indice].longueur_chemin +1 ;
	  				
	};
      }
      else{//SInon on ajout un mur si contrainte
	liste_piece[indice].murs[w] = 1;	//fprintf(stderr," SINON (adja)\n");
  		
      }
  	
    }else{
     liste_piece[indice] .murs[w] = 1;
  	
  	
    }
  
  }
    laby[i][k][j] = VUE;
  return liste_piece[indice].longueur_chemin+1;
}



void determine_i_k_j(int indice,int* i,int* k,int* j){
  int tmp;
  *k= (int)(indice / (LARGEUR*HAUTEUR));
  tmp = (int)(indice -(LARGEUR*HAUTEUR*(*k)));
  *j = (int)(tmp / LARGEUR);
  *i = (int)(tmp - LARGEUR * (*j));

}

int calcul_indice(int i,int k,int j){
  return ((i+(LARGEUR*j))+(LARGEUR*HAUTEUR*k));
}
void calcul_position_point(int indice,piece_laby* p){
  int i,j,k; // i largeur, j hauteur,k profondeur


  /*Calcul point bas gauche piece*/
  determine_i_k_j(indice,&i,&k,&j);
  p->pos_bg =creer_point( TAILLE_PIECE*i,  TAILLE_PIECE*k, TAILLE_PIECE*j );
	

}

file file_piece_a_afficher_labyrinthe(piece_laby liste_pieces[LARGEUR*HAUTEUR*PROFONDEUR]){
 file pieces_a_afficher = creer_file_vide();
 file pieces_a_afficher2 = creer_file_vide();
 element indice_piece_courante ; indice_piece_courante.indice=PIECE_DEPART;
 element indice_voisin= defile(liste_pieces[PIECE_DEPART].adjacent);

// fprintf(stderr," liste_pieces adj  %d \n" , indice_voisin.indice);
 //piece_laby piece_courante = liste_pieces[indice_piece_courante.indice]; // depart a redefinir
 struct_cellule* piece_adjacent = liste_pieces[indice_piece_courante.indice].adjacent->debut_file;
 int i,k,j;
 int laby[LARGEUR][HAUTEUR][PROFONDEUR];
 initilisation_labyrinthe(laby);

 //fprintf(stderr," dans file_piece_a_afficher \n");

 /*piece de depart du labyrinthe*/
 pieces_a_afficher= enfile(pieces_a_afficher,indice_piece_courante);
 determine_i_k_j(indice_piece_courante.indice,&i,&k,&j);
 laby[i][k][j] = VUE;

 /*creation de la file de piece a afficher*/
 while(!file_est_vide(pieces_a_afficher)){
   /*On recupere la piece courante*/
   indice_piece_courante = defile(pieces_a_afficher);
   pieces_a_afficher2 = enfile(pieces_a_afficher2,indice_piece_courante);
   /*On recupere la file d'adjacent de cette piece*/
   if(liste_pieces[indice_piece_courante.indice].adjacent != NULL && liste_pieces[indice_piece_courante.indice].adjacent->debut_file != NULL){
     piece_adjacent =liste_pieces[indice_piece_courante.indice].adjacent->debut_file;
   }
   //  fprintf(stderr," bllllllllldans file_piece_a_afficher \n");

   
   /*On traite la file d'adjacence*/
   while(piece_adjacent != NULL){
    
     indice_voisin = piece_adjacent->objet;
     // fprintf(stderr," %p dans file_piece_a_afficher %d indice_voisin %p \n" ,piece_adjacent, indice_voisin.indice,piece_adjacent->suivant);
     determine_i_k_j(indice_voisin.indice,&i,&k,&j);
     if(laby[i][k][j] == NON_VUE){
       laby[i][k][j] = VUE;
       pieces_a_afficher = enfile(pieces_a_afficher,indice_voisin);

     }
     piece_adjacent = piece_adjacent->suivant;
   }
   /******************************/
 }

 return pieces_a_afficher2;
}

void afficher_labyrinthe(file pieces_a_afficher,piece_laby liste_pieces[LARGEUR*HAUTEUR*PROFONDEUR]){
  int indice;
  struct_cellule* iterateur_piece_a_afficher  = pieces_a_afficher->debut_file;
  int i= 0;
  
 
  //fprintf(stderr," dans afficher_lab \n");
  while(iterateur_piece_a_afficher!=NULL){
		// fprintf(stderr," dans afficher_lab %d %p  %p \n",i ,iterateur_piece_a_afficher , iterateur_piece_a_afficher->suivant); i++;
	  indice = iterateur_piece_a_afficher->objet.indice;
	  if(indice == indice_piece_final){
	   visualiser_piece_laby_final(liste_pieces[indice]);
	  
	  }
	  else if(indice == PIECE_DEPART){
	   	visualiser_piece_laby_depart(liste_pieces[indice]);
	  
	  }else{
		visualiser_piece_laby(liste_pieces[indice]);
		
	   }
	   tracer_elements_piece(liste_pieces[indice]);
	   iterateur_piece_a_afficher = iterateur_piece_a_afficher->suivant;
	}		 

}

void tracer_elements_piece(piece_laby piece_courante){
	int type_piece = piece_courante.type_piece;
	int type_element;
	
	file test= liste_types_pieces[type_piece].objets;
//fprintf(stderr,"test tracer_element %p \n",test->debut_file);
	if(!file_est_vide(test)){
		struct_cellule* iterateur_element_a_afficher = test->debut_file;
		 
		 while(iterateur_element_a_afficher != NULL){
				element el = iterateur_element_a_afficher->objet;
				type_element = el.o->obj[0];
				if(type_element == 2){
					deduire_position_element(el,piece_courante);
				}
		
				tracer_element_obj(el);
				iterateur_element_a_afficher = iterateur_element_a_afficher -> suivant;
		}
	}

}

void deduire_position_element(element el,piece_laby piece_courante){
	int x = getX(piece_courante.pos_bg) ;
	int y = getY(piece_courante.pos_bg) ;
	int z = getZ(piece_courante.pos_bg);
	int indice_mur = el.o->obj[3];
	switch(indice_mur){
		case 0:
			el.o->obj[4]=x+TAILLE_PIECE/2;
			el.o->obj[5]=y;
			el.o->obj[6]=z+TAILLE_PIECE/2;
		break;
		
		case 1:
			el.o->obj[4]= x+TAILLE_PIECE/2;
			el.o->obj[5]= y+TAILLE_PIECE/2;
			el.o->obj[6]= z;		
		break;
		
		case 2:
			el.o->obj[4]= x+TAILLE_PIECE/2;
			el.o->obj[5]= y+TAILLE_PIECE;
			el.o->obj[6]= z+TAILLE_PIECE/2;;		
		break;

		case 3:
			el.o->obj[4]=x+TAILLE_PIECE/2;
			el.o->obj[5]=y+TAILLE_PIECE/2;
			el.o->obj[6]=z+TAILLE_PIECE;		
		break;

		case 4:
			el.o->obj[4]=x+TAILLE_PIECE;
			el.o->obj[5]=y+TAILLE_PIECE/2;
			el.o->obj[6]=z+TAILLE_PIECE/2;		
		break;
		
		case 5:
			el.o->obj[4]=x;
			el.o->obj[5]=y+TAILLE_PIECE/2;
			el.o->obj[6]=z+TAILLE_PIECE/2;		
		break;
	}
}
void visualiser_piece_laby_final(piece_laby p){

	
  int x1=(int)getX(p.pos_bg);
  int x2=x1+1*TAILLE_PIECE;
  int y1=(int)getY(p.pos_bg);
  int y2=y1+TAILLE_PIECE;
  int z1=(int)getZ(p.pos_bg);
  int z2=z1+TAILLE_PIECE;
	
  glBegin(GL_QUADS);
  //cyan
	
  if(p.murs[0]==1){
    glColor3f(0.83, 0.53, 0.06);
    glVertex3f(x1, y1, z2);
    glVertex3f(x1, y1, z1);
    glVertex3f(x2, y1, z1);
    glVertex3f(x2, y1, z2);
		
  }	
  // jaune
    
  if(p.murs[1]==1){
    glColor3f(0.75, 0.83, 0.06);
    glVertex3f(x1, y1, z1);
    glVertex3f(x2, y1, z1);
    glVertex3f(x2, y2, z1);
    glVertex3f(x1, y2, z1);
  }
      
  //rouge
  if(p.murs[2]==1){
	   
     glColor3f(0.83, 0.53, 0.6);
   
    glVertex3f(x1, y2, z2);
    glVertex3f(x2, y2, z2);
    glVertex3f(x2, y2, z1);
    glVertex3f(x1, y2, z1);
  }
  // bleu 0
  if(p.murs[3]==1){
    glColor3f(0.75, 0.83, 0.06);
    
    glVertex3f(x1, y1, z2);
    glVertex3f(x1, y2, z2);
    glVertex3f(x2, y2, z2);
    glVertex3f(x2, y1, z2);
  }
		
  // rose
  if(p.murs[4]==1){
    glColor3f(0.36, 0.83, 0.06);
    glVertex3f(x2, y1, z2);
    glVertex3f(x2, y2 ,z2);
    glVertex3f(x2, y2, z1);
    glVertex3f(x2, y1, z1);
		
  }
  //vert
  if(p.murs[5]==1){
    // glColor3f(0, 0.9, 0);
    glColor3f(0.36, 0.83, 0.06);
    
    glVertex3f(x1, y1, z2);
    glVertex3f(x1, y2, z2);
    glVertex3f(x1, y2, z1);
    glVertex3f(x1, y1, z1);

	}
}

element creer_pomme(point* p){
	type_objet* pmm=allocation_memoire(1,sizeof(type_objet));
	element pomme;
	pomme.o = pmm;
	pomme.o->obj[0]=1;// sphere
	pomme.o->obj[1]=12;//pas sphere
	pomme.o->obj[2]=1;//rayon
	pomme.o->obj[3]=(int)getX(p)+TAILLE_PIECE/2;
	pomme.o->obj[4]=(int)getY(p)+TAILLE_PIECE/2;
	pomme.o->obj[5]=(int)getZ(p) + pomme.o->obj[2];
	pomme.o->obj[6]=accomplit;
	
  point* pc =creer_point((float) getX(p)+TAILLE_PIECE/3,(float) (getY(p) +TAILLE_PIECE/3), (float) (getZ(p)+pomme.o->obj[2]));
  element cube = creer_cube(pc,pomme.o->obj[2]*4);
  
  tracer_sphere(pomme);
  if(pomme.o->obj[6] == 0){
  	tracer_cube(cube,0.5);
  }
  return pomme;

}

element creer_bonus(int mur){

	type_objet* bns=allocation_memoire(1,sizeof(type_objet));
	element bonus;
	bonus.o = bns;
	bonus.o->obj[0]=2;// pomme
	bonus.o->obj[1]=12;//pas sphere
	bonus.o->obj[2]=1;//rayon
	bonus.o->obj[3]=mur;//mur d'accroche
	bonus.o->obj[4]=-1;
	bonus.o->obj[5]=-1;
	bonus.o->obj[6]=-1;
	
	return bonus;
}

element creer_cube(point* p,int taille){
	element cube; //mon_allocation(1,sizeof(type_objet));
	type_objet* cb=allocation_memoire(1,sizeof(type_objet));
	cube.o = cb;
	cube.o->obj[0]=0;// cube
	cube.o->obj[1]=taille;//taille
	cube.o->obj[2]=(int)getX(p);
	cube.o->obj[3]=(int)getY(p);
	cube.o->obj[4]=(int)getZ(p);
	
	return cube;
}
void tracer_element_obj(element el){
	int type_e = (int)(el.o->obj[0]);
	switch(type_e){
		case 0://cas cube
			tracer_cube(el,1.0);
		break;
		
		case 1://cas sphere
			tracer_sphere(el);
		break;
		
		case 2://bonus  
		    glColor3f(0.37, 0.80, 0.85);
		    tracer_sphere(el);
			//tracer_pilier(el);
		break;
		case 3://cas rectangle/pilier
			//tracer_pilier(el);
		break;
	
	}
}

void tracer_cube(element el,float transparence){
	
  int x1=(int)el.o->obj[2];
  int x2=x1+(int)el.o->obj[1];
  int y1=(int)el.o->obj[3];
  int y2=y1+(int)el.o->obj[1];
  int z1=(int)el.o->obj[4];
  int z2=z1+(int)el.o->obj[1];
  glBegin(GL_QUADS);
    glEnable(GL_BLEND);
 	glBlendFunc(GL_SRC_ALPHA,GL_ONE);
    glColor4f(1, 0, 0,transparence);

    glVertex3f(x1, y1, z2);
    glVertex3f(x1, y1, z1);
    glVertex3f(x2, y1, z1);
    glVertex3f(x2, y1, z2);
		

    glVertex3f(x1, y1, z1);
    glVertex3f(x2, y1, z1);
    glVertex3f(x2, y2, z1);
    glVertex3f(x1, y2, z1);
 

    glVertex3f(x1, y2, z2);
    glVertex3f(x2, y2, z2);
    glVertex3f(x2, y2, z1);
    glVertex3f(x1, y2, z1);

    
    glVertex3f(x1, y1, z2);
    glVertex3f(x1, y2, z2);
    glVertex3f(x2, y2, z2);
    glVertex3f(x2, y1, z2);
	
    glVertex3f(x2, y1, z2);
    glVertex3f(x2, y2 ,z2);
    glVertex3f(x2, y2, z1);
    glVertex3f(x2, y1, z1);
    
    glVertex3f(x1, y1, z2);
    glVertex3f(x1, y2, z2);
    glVertex3f(x1, y2, z1);
    glVertex3f(x1, y1, z1);

	glEnd();
  

}
void tracer_sphere(element el){
	point* p = creer_point((float)(el.o->obj[3]),(float)(el.o->obj[4]),(float)(el.o->obj[5]));
	int rayon = el.o->obj[2];
	int pas = el.o->obj[1];
	afficherSphere(rayon,p,pas);
}


void visualiser_piece_laby_depart(piece_laby p){

	
  int x1=(int)getX(p.pos_bg);
  int x2=x1+TAILLE_PIECE;
  int y1=(int)getY(p.pos_bg);
  int y2=y1+TAILLE_PIECE;
  int z1=(int)getZ(p.pos_bg);
  int z2=z1+TAILLE_PIECE;
 
  pomme=creer_pomme(p.pos_bg); 
  
  
  glBegin(GL_QUADS);
  //cyan
	
  if(p.murs[0]==1){
    glColor3f(0.85, 0.65, 0.37);
    glVertex3f(x1, y1, z2);
    glVertex3f(x1, y1, z1);
    glVertex3f(x2, y1, z1);
    glVertex3f(x2, y1, z2);
		
  }	
  // jaune
    
  if(p.murs[1]==1){
    glColor3f(0.80, 0.85, 0.37);
    glVertex3f(x1, y1, z1);
    glVertex3f(x2, y1, z1);
    glVertex3f(x2, y2, z1);
    glVertex3f(x1, y2, z1);
  }
      
  //rouge
  if(p.murs[2]==1){
	   
   glColor3f(0.85, 0.65, 0.37);
   
    glVertex3f(x1, y2, z2);
    glVertex3f(x2, y2, z2);
    glVertex3f(x2, y2, z1);
    glVertex3f(x1, y2, z1);
  }
  // bleu 0
  if(p.murs[3]==1){
    glColor3f(0.80, 0.85, 0.37);
    
    glVertex3f(x1, y1, z2);
    glVertex3f(x1, y2, z2);
    glVertex3f(x2, y2, z2);
    glVertex3f(x2, y1, z2);
  }
		
  // rose
  if(p.murs[4]==1){
    glColor3f(0.58 ,0.85, 0.37);
    glVertex3f(x2, y1, z2);
    glVertex3f(x2, y2 ,z2);
    glVertex3f(x2, y2, z1);
    glVertex3f(x2, y1, z1);
		
  }
  //vert
  if(p.murs[5]==1){
    // glColor3f(0, 0.9, 0);
    glColor3f(0.58 ,0.85, 0.37);
    
    glVertex3f(x1, y1, z2);
    glVertex3f(x1, y2, z2);
    glVertex3f(x1, y2, z1);
    glVertex3f(x1, y1, z1);

	} 
	glEnd();
}
void visualiser_piece_laby(piece_laby  p){// different de afficher piece laby
	
  int x1=(int)getX(p.pos_bg);
  int x2=x1+TAILLE_PIECE;
  int y1=(int)getY(p.pos_bg);
  int y2=y1+TAILLE_PIECE;
  int z1=(int)getZ(p.pos_bg);
  int z2=z1+TAILLE_PIECE;
  
  
  glBegin(GL_QUADS);
  //cyan
	
  if(p.murs[0]==1){
    glColor3f(0.07, 0.55, 0.45);
    glVertex3f(x1, y1, z2);
    glVertex3f(x1, y1, z1);
    glVertex3f(x2, y1, z1);
    glVertex3f(x2, y1, z2);
		
  }	
  // jaune
    
  if(p.murs[1]==1){
    glColor3f(0.7, 0.4, 0.55);
    glVertex3f(x1, y1, z1);
    glVertex3f(x2, y1, z1);
    glVertex3f(x2, y2, z1);
    glVertex3f(x1, y2, z1);
  }
      
  //rouge
  if(p.murs[2]==1){
		
    //glColor3f(0.9, 0, 0);
    glColor3f(0.07, 0.55, 0.45);
    glVertex3f(x1, y2, z2);
    glVertex3f(x2, y2, z2);
    glVertex3f(x2, y2, z1);
    glVertex3f(x1, y2, z1);
  }
  // bleu 0
  if(p.murs[3]==1){
    //glColor3f(0, 0, 0.9);
    glColor3f(0.7, 0.4, 0.55);
    
    glVertex3f(x1, y1, z2);
    glVertex3f(x1, y2, z2);
    glVertex3f(x2, y2, z2);
    glVertex3f(x2, y1, z2);
  }
		
  // rose
  if(p.murs[4]==1){
    glColor3f(0.55, 0.07, 0.4);
    glVertex3f(x2, y1, z2);
    glVertex3f(x2, y2 ,z2);
    glVertex3f(x2, y2, z1);
    glVertex3f(x2, y1, z1);
		
  }
  //vert
  if(p.murs[5]==1){
    // glColor3f(0, 0.9, 0);
    glColor3f(0.55, 0.07, 0.4);
    
    glVertex3f(x1, y1, z2);
    glVertex3f(x1, y2, z2);
    glVertex3f(x1, y2, z1);
    glVertex3f(x1, y1, z1);

		
  }
  glEnd();
}

