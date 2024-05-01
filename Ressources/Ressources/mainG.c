#include "Graphe.h"
#include "Reseau.h"
#include "Chaine.h"
#include "ArbreQuat.h"
#include "Hachage.h"



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
        printf("\nVous avez choisi la méthode 1 avec liste chaînée avec le fichier %s\n pour la réorganisation du réseau.\n",nom_fichier);
        Reseau* r_lc = reconstitueReseauListe(chaine);
        printf("Il y a %d liaisons et %d commodites dans ce réseau\n",nbLiaisons(r_lc),nbCommodites(r_lc));
        int val = reorganiseReseau(r_lc);
        if(val==0){
            printf("\nVrai, pour toute arête du graphe, le nombre de chaı̂nes qui passe par cette arête est inférieur à gamma.\n");
        }
        else{
            printf("\nFaux,les arêtes indiquées plus haut sont supérieures au gamma !\n");
        }
        printf("Fin du programme.\n\n");
        liberer_reseau(r_lc);
        liberer_Chaines(chaine);
        return 0;
    }
    else if(num_meth == 2){
        int M; //M va stocker la taille de la table.
        printf("\nVous avez choisi la méthode 2 avec table de hachage avec le fichier %s pour la réorganisation du réseau.\n",nom_fichier);
        printf("Veuillez rentrer en entier pour la taille de la table de Hache : ");scanf(" %d", &M);
        Reseau* r_h = reconstitueReseauHachage(chaine,M);
        printf("Il y a %d liaisons et %d commodites dans ce réseau\n\n",nbLiaisons(r_h),nbCommodites(r_h));
        int val = reorganiseReseau(r_h);
        if(val==0){
            printf("\nVrai, pour toute arête du graphe, le nombre de chaı̂nes qui passe par cette arête est inférieur à gamma.\n");
        }
        else{
            printf("\nFaux,les arêtes indiquées plus haut sont supérieures au gamma !\n");
        }
        printf("Fin du programme.\n\n");
        liberer_reseau(r_h);
        liberer_Chaines(chaine);
        //la table de hachage est libérée dans reconstitueReseauHachage.
        return 0;
    }
     else if(num_meth == 3){
        printf("\nVous avez choisi la méthode 3 avec arbre quaternaire avec le fichier %s pour la réorganisation du réseau.\n",nom_fichier);
        Reseau* r_a = reconstitueReseauArbre(chaine);
        printf("Il y a %d liaisons et %d commodites dans ce réseau\n",nbLiaisons(r_a),nbCommodites(r_a));
        int val = reorganiseReseau(r_a);
        if(val==0){
            printf("\nVrai, pour toute arête du graphe, le nombre de chaı̂nes qui passe par cette arête est inférieur à gamma.\n");
        }
        else{
            printf("\nFaux,les arêtes indiquées plus haut sont supérieures au gamma !\n");
        }
        printf("Fin du programme.\n\n");
        liberer_reseau(r_a);
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
    return 0;

}
    








/*


    //FILE *f = fopen("00014_burma.cha", "r"); 
    //FILE *f = fopen("05000_USA-road-d-NY.cha", "r"); 
    //FILE *f = fopen("07397_pla.cha", "r"); 

    
    Chaines* test = lectureChaines(f);
    Reseau* r_lc = reconstitueReseauListe(test);
    int val = reorganiseReseau(r_lc);
    liberer_Chaines(test);
    liberer_reseau(r_lc);
    

    //Reseau* r = reconstitueReseauListe(test); 
    //int val = reorganiseReseau(r);
   /* Graphe* g = creerGraphe(r);
    Cell_entier* l =  arborescence_chemins(g,u,v);
    
    if(l==NULL){
        printf("liste null\n");
    }
    while(l){
        printf("num: %d \n",l->num);
        l = l->suiv;
    }
    int chemin = plus_petit_nb_aretes(g,u,v);
    printf("la lg du plus petit chemin entre %d et %d est %d\n",u,v,chemin);

//TEST DE LA QUESTION 7.1
    int i=0;
    while(i<g->nbsom-1){
        int s = g->T_som[i]->num;
        double x = g->T_som[i]->x;
        double y = g->T_som[i]->y;
        printf("sommet : %d x=%.2f et y=%.2f\n",s,x,y);
        Cellule_arete* voisin = g->T_som[i]->L_voisin;
        while(voisin){
            printf("arrete entre u=%d et v=%d\n",voisin->a->u,voisin->a->v);
            voisin = voisin->suiv;
        }
        i++;
    }

    
    return 0;
}
*/