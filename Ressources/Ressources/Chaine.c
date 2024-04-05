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
        //printf("num chaine : %d et nb_points = %d\n",num_chaine,nb_points);
        CellChaine* new_lc = malloc(sizeof(CellChaine));
        new_lc->numero = num_chaine;
        CellPoint* tete_l;
        for(int i=0;i<nb_points;i++){
            double px,py;
            CellPoint* new_points = malloc(sizeof(CellPoint));
            fscanf(f,"%lf %lf",&px,&py);
            new_points->x = px;
            new_points->y = py;
            //printf("x = %.2lf, y = %.2lf\n", px, py);
            
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
    //Check compilation Svalgrind --leak-check=full ./nom_de_votre_programme 


    while(courant_chaine!=NULL){

        CellPoint *chainePoint = courant_chaine->points;
        int nb_points = 0;

        //Ce while calcule le nombre de points de la chaine.
        while(chainePoint != NULL){
            nb_points++;
            chainePoint = chainePoint->suiv;
        }
        int num_chaine = courant_chaine->numero;
        fprintf(f,"%d %d ",num_chaine,nb_points);

        //Ce while ecrit les points dans le fichier.
        CellPoint *courant_point = courant_chaine->points;
        while(courant_point != NULL){
            fprintf(f,"%.2f %.2f ",courant_point->x,courant_point->y);
            courant_point = courant_point->suiv;
        }
        fprintf(f,"\n");
        courant_chaine = courant_chaine->suiv;
    }
    fclose(f);

}

void afficheChainesSVG(Chaines *C, char* nomInstance){
    //int i;
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

double longueurChaine(CellChaine *c){
    CellPoint* courant = c->points->suiv;
    CellPoint* prec = c->points;
    double longueur = 0.0;

    while(courant != NULL){
        longueur += sqrt(pow((courant->x - prec->x),2) + pow((courant->y - prec->y),2));
        prec = courant;
        courant =  courant->suiv;
    }
    return longueur;
}

double longueurTotale(Chaines *C){

    CellChaine* c_chaine = C->chaines;
    double total =0.0;
    while(c_chaine != NULL){
        total += longueurChaine(c_chaine);
        c_chaine = c_chaine->suiv;
    }
    return total;

}


int comptePointsTotal(Chaines *C){
    int nb_points = 0;
    CellChaine* courant_chaine = C->chaines;

    while(courant_chaine != NULL){
        CellPoint* courant_point = courant_chaine->points;
        while(courant_point != NULL){
            nb_points++;
            courant_point = courant_point->suiv;
        }
        courant_chaine = courant_chaine->suiv;
    }
    return nb_points;
}

//Fonction de libération d'espace

//Libérer CellPoint
void liberer_CellPoint(CellPoint* cp){
    if(cp){
        CellPoint* tmp = NULL;
        while(cp){
            tmp = cp->suiv;
            free(cp);
            cp = tmp; 
        }
    }
}

//Libérer CellChaine
void liberer_CellChaine(CellChaine* cc){
    if(cc){
        CellChaine* tmp = NULL;
        while(cc){
            liberer_CellPoint(cc->points);
            tmp = cc->suiv;
            free(cc);
            cc=tmp; 
        }
    }
}

//Libérer Chaines
void liberer_Chaines(Chaines *c){
    if(c){
        liberer_CellChaine(c->chaines);
        free(c); 
    }
}