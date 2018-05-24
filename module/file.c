#include <stdio.h>
#include <stdlib.h>
#include "mon_allocation.h"
#include "file.h"

file creer_file_vide(){
  return NULL;
}

int file_est_vide(file f){
  if(f==NULL || (f->debut_file == NULL && f->fin_file == NULL)){
    return 1;
  }
  return 0;
}

file enfile(file f, element el){
  if(file_est_vide(f)){
    struct_suivit_cellule* nouveau;
    struct_cellule* debut;
    debut =allocation_memoire(1,sizeof(struct_cellule));
    nouveau=allocation_memoire(1,sizeof(struct_suivit_cellule));
    debut->objet=el;
    debut->suivant=NULL;
    nouveau->fin_file=debut;
    nouveau->debut_file=debut;
    // fprintf(stderr,"la \n");
    return nouveau;
  }
  else{
    struct_cellule* nouvelle_fin;
    struct_cellule* tmp;
    tmp =allocation_memoire(1,sizeof(struct_cellule));
    //fprintf(stderr,"ici donction file\n");
    nouvelle_fin=allocation_memoire(1,sizeof(struct_cellule));
    nouvelle_fin->objet=el;
    nouvelle_fin->suivant=NULL;
    tmp=f->fin_file;
    tmp->suivant=nouvelle_fin;
    f->fin_file=nouvelle_fin;

    return f;
  }

}

file vider_file(file f){
  file f2=creer_file_vide();
  free(f);
  return f2;

}
element defile ( file f){
  element nombre;
  struct_cellule* nouveau_debut;
  
  if( file_est_vide(f)){ // cas file vide
     fprintf(stderr," Erreur file vide \n");
    exit(EXIT_FAILURE);
   
  }
  else if(f->debut_file==NULL || f->fin_file==NULL){
    fprintf(stderr," Debut file vide \n");
    exit(EXIT_FAILURE);
    
  }
  
  if(f->fin_file == f->debut_file){ // cas un seul element
    nombre=f->fin_file->objet;
   // fprintf(stderr,"1 %p %p \n",f->debut_file,f->fin_file);
    f->debut_file = NULL;
    f->fin_file = NULL;
   

    // free(f->debut_file);
    return nombre;
    
  }
  else{ // cas liste plus d'un seul element 
    nouveau_debut=f->debut_file;
    nombre=nouveau_debut->objet;
    f->debut_file=nouveau_debut->suivant;
    free(nouveau_debut);
    return nombre;
  }

}

  

void afficher_file(file f){
  struct_cellule* tmp;
  if(f->debut_file!=NULL){
    fprintf(stdout,"< ");
    tmp=f->debut_file;
    while(tmp->suivant!=NULL){
    //  fprintf(stdout,"%d , ",tmp->objet);
      tmp=tmp->suivant;
    }
    //fprintf(stdout,"%d > \n",tmp->objet);
  }
  else{
    fprintf(stdout,"< file vide >");
  }
}


/*
int main(){
  int i,nombre;
  file f=creer_file_vide();
  for (i=5;i<10;i++){
    f=enfile(f,i);
  }
  
  afficher_file(f);
 for (i=4;i<11;i++){
  fprintf(stdout,"--------");
  nombre=defile(f);
  fprintf(stdout,"%d > \n",nombre);
  afficher_file(f);
 }
}
*/
