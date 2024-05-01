#include "Reseau.h"
#include "Chaine.h"
#include "ArbreQuat.h"
#include "Hachage.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>


int main(int argc,char** argv){

    if(argc != 3){
        printf("Usage: %s fichier.cha n (n un entier entre 1 et 3 pour choisir la méthode.)\n",argv[0]);
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
        printf("\nVous avez choisi la méthode 1 avec liste chaînée avec le fichier %s\n",nom_fichier);
        Reseau* reseau1 = reconstitueReseauListe(chaine);

        printf("Il y a %d liaisons et %d commodites dans ce réseau\n",nbLiaisons(reseau1),nbCommodites(reseau1));
        FILE *f1 = fopen("Reseau_avec_liste.txt", "w"); 
        ecrireReseau(reseau1,f1);
        afficheReseauSVG(reseau1,"Reseau_avec_liste"); 
        printf("Un fichier 'Reseau_avec_liste.txt' et 'Reseau_avec_liste.html' ont été créé dans votre répertoire.\n");
        printf("Fin du programme.\n\n");
        
        
        liberer_reseau(reseau1);
        liberer_Chaines(chaine);
        return 0;
    }
    else if(num_meth == 2){
        int M; //M va stocker la taille de la table.
        printf("\nVous avez choisi la méthode 2 avec table de hachage avec le fichier %s\n",nom_fichier);
        printf("Veuillez rentrer en entier pour la taille de la table de Hache : ");scanf(" %d", &M);
        Reseau* reseau2 = reconstitueReseauHachage(chaine,M);
        printf("Il y a %d liaisons et %d commodites dans ce réseau\n",nbLiaisons(reseau2),nbCommodites(reseau2));
        FILE *f2 = fopen("Reseau_avec_TDH.txt", "w"); 
        ecrireReseau(reseau2,f2);
        afficheReseauSVG(reseau2,"Reseau_avec_TDH");
        printf("Un fichier 'Reseau_avec_TDH.txt' et 'Reseau_avec_TDH.html' ont été créé dans votre répertoire.\n");
        printf("Fin du programme.\n\n");
        liberer_reseau(reseau2);
        liberer_Chaines(chaine);
        //la table de hachage est libérée dans reconstitueReseauHachage.
        return 0;
    }
    else if(num_meth == 3){
        printf("\nVous avez choisi la méthode 3 avec arbre quaternaire avec le fichier %s\n",nom_fichier);
        Reseau* reseau3 = reconstitueReseauArbre(chaine);
        FILE *f3 = fopen("Reseau_avec_arbreQ.txt", "w");
        printf("Il y a %d liaisons et %d commodites dans ce réseau\n",nbLiaisons(reseau3),nbCommodites(reseau3));
        afficheReseauSVG(reseau3,"Reseau_avec_arbreQ");
        ecrireReseau(reseau3,f3);
        printf("Un fichier 'Reseau_avec_arbreQ.txt' et 'Reseau_avec_arbreQ.html'  ont été créé dans votre répertoire.\n");
        printf("Fin du programme.\n\n");
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