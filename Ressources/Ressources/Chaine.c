#include <stdio.h>
#include <stdlib.h>
#include "Chaine.h"

Chaines* lectureChaine(FILE *f){
    if(f == NULL){
        printf("Erreur d'ouverture du fichier\n");
        exit(1);
    }
    Chaines* new_chaine = malloc(sizeof(Chaines));

    int nbchaine;
    int gamma;
    char buffer[256];

    fgets(buffer,256,f);
    sscanf(buffer,"NbChain: %d",&nbchaine);
    fgets(buffer,256,f);
    sscanf(buffer,"Gamma: %d",&gamma);
    new_chaine->gamma = gamma;
    new_chaine->nbChaines = nbchaine;

    int num_chaine;
    int nb_points;
    CellChaine* tete_lc;

    while((fgets(buffer,256,f)!=NULL)){
        sscanf(buffer,"%d %d %s",&num_chaine,&nb_points,buffer);
        
        CellChaine* new_lc = malloc(sizeof(CellChaine));
        new_lc->numero = num_chaine;

        CellPoint* tete_l;
        for(int i=0;i<nb_points;i++){
            float px,py;
            CellPoint* new_points = malloc(sizeof(CellPoint));
            sscanf(buffer,"%.2f %.2f %s",&px,&py,buffer);
            new_points->x = px;
            new_points->y = py;
            if(i==0){
                new_points->suiv = NULL;
                tete_l = new_points;
            }else{
                new_points->suiv = tete_l;
                tete_l = new_points;
            }
        }
        new_lc->points = tete_l;
        
        if(num_chaine ==0){
            new_lc->suiv = NULL;
            tete_lc = new_lc;
        }
        else{
            new_lc->suiv = tete_lc;
            tete_lc = new_lc;
        }
    }
    new_chaine->chaines = tete_lc;
    return new_chaine; 
}



void ecrireChaine(Chaines *C, FILE *f){
    if(f == NULL){
        printf("Erreur d'ouverture du fichier\n");
        exit(1);
    }
    fprintf(f,"NbChain: %d\n",C->nbChaines);
    fprintf(f,"Gamma: %d\n",C->gamma);

    CellChaine *courant_chaine = C->chaines;
    
    //Pas fini, problème avec nb points donc on fait un buffer
    //Check compilation S
    while(courant_chaine!=NULL){
        fprintf(f,"%d ",courant_chaine->numero);

        CellPoint* courant_points = courant_chaine->points;
        char buffer[256];
        int nb_points;
        while(courant_points!=NULL){
            sscanf(buffer,"%f %f %s",courant_points->x,courant_points->y,buffer);
            courant_points = courant_points->suiv;
            nb_points++;
        }
        
        fprintf(f,"%d %s\n",nb_points,buffer);
    }
}

 
int main(){
    FILE *f = fopen("00014_burma.cha", "r");
    Chaines * test = lectureChaine(f); 
    printf("%d\n", test->nbChaines); 
    printf("%d\n", test->gamma);
    ecrireChaine(test, "test.txt"); 
    return 0; 
}
