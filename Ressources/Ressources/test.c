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
int main() {
    /*int num,nb;
    char buffer[100];
    double px,py;
    FILE *f = fopen("test.txt", "r");
    fscanf(f, "%d %d", &num, &nb);
    printf("num= %d et nb = %d\n",num,nb);

    fscanf(f, "%lf %lf", &px, &py);
    printf("x = %.2lf, y = %.2lf\n", px, py);


    fscanf(f, "%lf %lf", &px, &py);
    printf("x = %.2lf, y = %.2lf\n", px, py);*/

    
    
    /*sscanf(buffer,"%d %d",&num,&nb); 
    printf("%d et %d\n", num,nb);

    sscanf(buffer,"%lf %lf",&px,&py);
    printf("x = %.2lf, y = %.2lf\n", px, py);*/



    FILE *f = fopen("00014_burma.cha", "r");
    Chaines * test = lectureChaine(f); 
    while(test->chaines){
        printf("%d ",test->chaines->numero);
        while(test->chaines->points){
            printf("%.2f %.2f ",test->chaines->points->y,test->chaines->points->x);
            test->chaines->points = test->chaines->points->suiv;
        }
        printf("\n");
        test->chaines = test->chaines->suiv;
    }
    printf("\n");
   /* double x, y;
    char reste_de_la_ligne[100]; // Taille arbitraire pour stocker le reste de la ligne

    FILE *fichier = fopen("test.txt", "r"); // Ouvrir le fichier en lecture
    if (fichier == NULL) {
        printf("Erreur: Impossible d'ouvrir le fichier.\n");
        return 1;
    }

    // Lire les deux premiers nombres de la première ligne du fichier
    if (fscanf(fichier, "%lf %lf", &x, &y) != 2) {
        printf("Erreur lors de la lecture des deux premiers nombres.\n");
        fclose(fichier);
        return 1;
    }
    printf("x = %.2f, y = %.2f\n", x, y);

    // Lire le reste de la première ligne
    fscanf(fichier, "%s"); // Ignorer le reste de la ligne
    fgets(reste_de_la_ligne, sizeof(reste_de_la_ligne), fichier);
    printf("Reste de la ligne : %s\n", reste_de_la_ligne);

    fclose(fichier); // Fermer le fichier*/
}

