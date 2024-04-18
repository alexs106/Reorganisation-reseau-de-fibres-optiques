#include "Reseau.h"
#include "Chaine.h"
#include "ArbreQuat.h"
#include "Hachage.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

Chaines* generationAleatoire(int nbChaines, int nbPointsChaine, int xmax,int ymax){
    Chaines* chaine = malloc(sizeof(Chaines));
    chaine->nbChaines = nbChaines;
    chaine->gamma = 3;
    
    srand(time(NULL));
    CellChaine* tete_lc;
    int i = 0;
    while(i < nbChaines){
        CellChaine* cell_chaine = malloc(sizeof(CellChaine));
        cell_chaine->numero = i;
        
        CellPoint* tete_lp;
        int j = 0;
        while(j<nbPointsChaine){
            CellPoint* cell_point = malloc(sizeof(CellPoint));
            cell_point->x = (double)rand() / ((double)RAND_MAX / xmax);
            cell_point->y = (double)rand() / ((double)RAND_MAX / ymax);
            
            if(j==0){
                cell_point->suiv = NULL;
                tete_lp = cell_point;
            }else{
                cell_point->suiv = tete_lp;
                tete_lp = cell_point;
            }
            j++;
        }
        cell_chaine->points = tete_lp;

        if(i ==0){
            cell_chaine->suiv = NULL;
            tete_lc = cell_chaine;
        }
        else{
            cell_chaine->suiv = tete_lc;
            tete_lc = cell_chaine;
        }
        i++;
    }
    chaine->chaines = tete_lc;
    return chaine;
}




int main(int argc,char** argv){
    /*TEST DE LA QUESTION 6.2
    FILE *f2 = fopen("temps_de_calcul_alea.txt", "w");
    Chaines* c = generationAleatoire(10,5,5,5);
    ecrireChaines(c,f2);*/


    /*TEST DE LA QUESTION 6.1
    char* nom_fichier = argv[1];
    FILE *f = fopen(nom_fichier, "r");
    if (f==NULL){
		printf("Erreur lors de l'ouverture du fichier \n");
		return -1;
	}
    int M;
    printf("Veuillez rentrer en entier pour la taille de la table de Hache : ");scanf(" %d", &M);

    Chaines* chaine = lectureChaines(f); 
    double temps_lc = 0;
    double temps_lc_debut;
    double temps_lc_fin;

    double temps_h = 0;
    double temps_h_debut;
    double temps_h_fin;

    double temps_a = 0;
    double temps_a_debut;
    double temps_a_fin;

    temps_lc_debut = clock();
    reconstitueReseauListe(chaine);
    temps_lc_fin = clock();

    temps_h_debut = clock();
    reconstitueReseauHachage(chaine,M);
    temps_h_fin = clock();

    temps_a_debut = clock();
    reconstitueReseauArbre(chaine);
    temps_a_fin = clock();

    temps_lc = ((double)(temps_lc_fin-temps_lc_debut))/CLOCKS_PER_SEC;
	temps_h = ((double)(temps_h_fin-temps_h_debut))/CLOCKS_PER_SEC;
    temps_a = ((double)(temps_a_fin-temps_a_debut))/CLOCKS_PER_SEC;

    FILE * fw=fopen("temps_de_calcul.txt","w");
	if (fw==NULL){
		printf("Erreur lors de l'ouverture du fichier \n");
		return -1;
	}
    fprintf(fw,"Temps de calcul pour le fichier %s\n",nom_fichier);
    fprintf(fw,"Liste chainée : %lf secondes\n",temps_lc);
    fprintf(fw,"Table de Hachage de taille %d : %lf secondes\n",M,temps_h);
    fprintf(fw,"Arbre quaternaire : %lf secondes\n",temps_a);
    fclose(f);*/

    double temps_lc = 0;
    double temps_lc_debut;
    double temps_lc_fin;

    double temps_h = 0;
    double temps_h_debut;
    double temps_h_fin;

    double temps_a = 0;
    double temps_a_debut;
    double temps_a_fin; 

    FILE *f2 = fopen("temps_calcul_lc.txt", "w");
    FILE *f3 = fopen("temps_calcul_ha.txt","w"); 
    //Taille de hachage : 10, 50, 100, 500, 1000

    for(int nbChaines=500; nbChaines<=5000; nbChaines+=500){
        //int nbChaines, int nbPointsChaine, int xmax,int ymax
        Chaines* chaine = generationAleatoire(nbChaines,100,5000,5000);
        int M = 10;  

        //ecrireChaines(chaine,f2);

        temps_lc_debut = clock();
        reconstitueReseauListe(chaine);
        temps_lc_fin = clock();

        temps_h_debut = clock();
        reconstitueReseauHachage(chaine,M);
        temps_h_fin = clock();

        temps_a_debut = clock();
        reconstitueReseauArbre(chaine);
        temps_a_fin = clock(); 

        temps_lc = ((double)(temps_lc_fin-temps_lc_debut))/CLOCKS_PER_SEC;
	    temps_h = ((double)(temps_h_fin-temps_h_debut))/CLOCKS_PER_SEC;
        temps_a = ((double)(temps_a_fin-temps_a_debut))/CLOCKS_PER_SEC;

        //fprintf(f2,"Temps de calcul pour le fichier %s\n","test_graphe.txt");
        fprintf(f2,"%d %lf\n",nbChaines, temps_lc);
        fprintf(f3,"%d %lf %lf\n",nbChaines, temps_h, temps_a);

        printf("%d\n", nbChaines); 
        //liberer_Chaines(chaine);
    }

    fclose(f2);
    fclose(f3); 
    
    return 0;
}

