#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "Chaine.h"
#include "SVGwriter.h"

Chaines* lectureChaines(FILE *f){
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

    // Lire chaque ligne du fichier
    int i = 0;
    while(i<nbchaine){
      
        fscanf(f,"%d %d",&num_chaine,&nb_points); 
        printf("num chaine : %d et nb_points = %d\n",num_chaine,nb_points);
        CellChaine* new_lc = malloc(sizeof(CellChaine));
        new_lc->numero = num_chaine;
        CellPoint* tete_l;
        for(int i=0;i<nb_points;i++){
            double px,py;
            CellPoint* new_points = malloc(sizeof(CellPoint));
            fscanf(f,"%lf %lf",&px,&py);
            new_points->x = px;
            new_points->y = py;
            printf("x = %.2lf, y = %.2lf\n", px, py);
            
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
        i++;
    }

    new_chaine->chaines = tete_lc;
    fclose(f); 
    return new_chaine;
}



void ecrireChaines(Chaines *C, FILE *f){
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
        char totalPoints[256]; 

        while(courant_points!=NULL){
            sprintf(buffer,"%f %f ",courant_points->x,courant_points->y);
            courant_points = courant_points->suiv;
            nb_points++;
            strcat(totalPoints,buffer); 
        }
        
        fprintf(f,"%d %s\n",nb_points,totalPoints);
    }
}

void afficheChainesSVG(Chaines *C, char* nomInstance){
    int i;
    double maxx=0,maxy=0,minx=1e6,miny=1e6;
    CellChaine *ccour;
    CellPoint *pcour;
    double precx,precy;
    SVGwriter svg;
    ccour=C->chaines;
    while (ccour!=NULL){
        pcour=ccour->points;
        while (pcour!=NULL){
            if (maxx<pcour->x) maxx=pcour->x;
            if (maxy<pcour->y) maxy=pcour->y;
            if (minx>pcour->x) minx=pcour->x;
            if (miny>pcour->y) miny=pcour->y;  
            pcour=pcour->suiv;
        }
    ccour=ccour->suiv;
    }
    SVGinit(&svg,nomInstance,500,500);
    ccour=C->chaines;
    while (ccour!=NULL){
        pcour=ccour->points;
        SVGlineRandColor(&svg);
        SVGpoint(&svg,500*(pcour->x-minx)/(maxx-minx),500*(pcour->y-miny)/(maxy-miny)); 
        precx=pcour->x;
        precy=pcour->y;  
        pcour=pcour->suiv;
        while (pcour!=NULL){
            SVGline(&svg,500*(precx-minx)/(maxx-minx),500*(precy-miny)/(maxy-miny),500*(pcour->x-minx)/(maxx-minx),500*(pcour->y-miny)/(maxy-miny));
            SVGpoint(&svg,500*(pcour->x-minx)/(maxx-minx),500*(pcour->y-miny)/(maxy-miny));
            precx=pcour->x;
            precy=pcour->y;    
            pcour=pcour->suiv;
        }
        ccour=ccour->suiv;
    }
    SVGfinalize(&svg);
}

double longueurChaine(CellChaine *c); 
