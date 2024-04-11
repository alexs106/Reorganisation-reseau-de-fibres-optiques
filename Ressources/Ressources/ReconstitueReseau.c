#include "Reseau.h"
#include "Chaine.h"
#include "ArbreQuat.h"
#include "Hachage.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>


int main(int argc,char** argv){
    
    if(argc != 3){
        printf("Usage: %s fichier.cha n (n un entier entre 1 et 3)\n",argv[0]);
        return 1;
    }

    char* nom_fichier = argv[1];
    FILE *f = fopen(nom_fichier, "r");
    if(f == NULL){
        printf("Erreur lors de l'ouverture du fichier\n");
        return 1;
    }

    int num_meth = atoi(argv[2]);
    Chaines * chaine = lectureChaines(f); 

    if(num_meth == 1){
        printf("Vous avez choisi la méthode 1 avec liste\n");
        Reseau* reseau1 = reconstitueReseauListe(chaine);
        FILE *f1 = fopen("fichier_res_avec_liste.txt", "w"); 
        ecrireReseau(reseau1,f1);
        afficheReseauSVG(reseau1,"reseau_avec_liste"); 

        liberer_reseau(reseau1);
        liberer_Chaines(chaine);
        return 0;
    }
    else if(num_meth == 2){
        int M; //M va stocker la taille de la table.
        printf("Vous avez choisi la méthode 2 avec table de hachage\n");
        printf("Veuillez rentrer en entier pour la taille de la table de Hache : ");scanf(" %d", &M);
        Reseau* reseau2 = reconstitueReseauHachage(chaine,M);
        FILE *f2 = fopen("fichier_res_avec_TDH.txt", "w"); 
        ecrireReseau(reseau2,f2);
        afficheReseauSVG(reseau2,"reseau_avec_TDH");

        liberer_reseau(reseau2);
        liberer_Chaines(chaine);
        //la table de hachage est libérée dans reconstitueReseauHachage.
        return 0;
    }
    else if(num_meth == 3){
        printf("Vous avez choisi la méthode 3 avec arbre quaternaire\n");
        Reseau* reseau3 = reconstitueReseauArbre(chaine);
        FILE *f3 = fopen("fichier_res_avec_arbreQ.txt", "w");
        ecrireReseau(reseau3,f3);
        afficheReseauSVG(reseau3,"reseau_avec_arbreQ");

        liberer_reseau(reseau3);
        liberer_Chaines(chaine);
        //l'arbre est libéré dans reconstitueReseauArbre.
        return 0;
    }
    else{
        printf("Usage: %s fichier.cha n (n un entier entre 1 et 3)\n",argv[0]);
        printf("Pour obtenir la méthode 1 (liste) n = 1\n");
        printf("Pour obtenir la méthode 2 (table de hachage) n = 2\n");
        printf("Pour obtenir la méthode 3 (arbre) n = 3\n");
        return 1;
    }
}