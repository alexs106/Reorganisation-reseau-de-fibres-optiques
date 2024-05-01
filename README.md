**Noah ALVES 21105881**

**Alejandra MORALES SAUCEDO 21214631**

**Description du projet**

Le projet a porté sur la réorganisation d'un réseau de fibres optiques d'une agglomération grace à différentes structures de données telles que une liste chaînée, une table de hachage, un arbre quaternaire et un graphe. 

Le projet se divise en deux parties : la reconstitution du réseau et la réorganisation du réseau.

Les réseau de fibres se compose d'un ensemble de câbles, chaque cable comportant un esemble de fibres optiques qui relient des clients. 

Pour la première partie, la reconstitution du réseau consiste à regrouper l'ensemble des fibres optiques de tous les opérateurs qui constituent le réseau de l'agglomération afin d'avoir un plan complet du réseau.

Pour la deuxième partie, la réorganisation du réseau consiste à répartir les chaînes de tronçons de fibres qui relient une pair de clients afin d'éviter les problème de sur-exploitation et longueurs excessives des châines. 

Un câble du réseau est un fourreau qui contient exactement gamma > 0 fibres optiques. Les câbles relient deux points du plan, soit des clients ou des concentrateurs qui eux permettent de relier des tronçons de fibres. Ces tronçons reliés par un même concentrateur forment une châine dans le réseau. Une châine relie deux points clients qu'on appelle une commodité, les extremités de cette chaîne.  

**Description des structures manipulés, description globale de votre code**
Partie 1 : Lecture, stockage et affichage des données. 
Cette partie est composée de l'exercice 1, cet exercice à pour but de reconstruire une instance d'une structure Chaines à partir d'un fichier, ou bien d'écrire le contenu d'une Chaines sur un fichier en respectant un format donné.
Nous pouvons événtuellement avoir une represenatation graphiques des instances grâçe à la fonction afficheChaineSVG, elle permet de créer un fichier SVG en HTML et qui sera lu depuis un explorateur internet.






Partie 2 : 


**Description schématique des algorithmes que nous avons crées**


**Réponses aux questions**

**_Exercice 4, question 2_**
Suite à notre test sur les points (x,y) avec *x* un entier allant de 1 à 10 et *y* un entier allant de 1 à 10, nous constatons que plusieurs cléfs ont la même valeurs, soit 88 cléfs sur 100 sont répétées au moins une fois sur notre test.  
De ce fait, la fonction *cle (x,y)* nous semble pas appropriée car elle peut engendrer plusieurs collisions. 
L'unicité de la cléf de hachage est essentielle pour diminuer les problèmes de collisions. 

***Exercice 6, question 1***
Quand on exécute les trois fonctions de reconstruction avec le temps de calcul pour les instances fournies, on observe que lorsqu'on utilise un nombre de chaînes très petit, les temps de calcul pour les 3 structures sont plutôt similaires. 

Pour une instance plus grande, si la table de hachage est de taille inférieure au nombre de chaînes, son temps de calcul resemble à celui de la liste chaînée, soit 40 fois plus long que celui de l'arbre quaternaire. 

Cependant, si la table de hachage est de taille supérieure ou égale au nombre de chaînes, sont  temps de calcul se rapproche à celui de l'arbre 

***Exercice 6, question 4***
Voir la section : Analyse commentée des performances de nos programmes




***Exercice 7, question 5***
# NOAH !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!


Pour améliorer la fonction on pourrait remplacer la matrice carré sommet-sommet par une matrice triangulaire qui nous permettrait d'économiser de l'espace mémoire et du temps de calcul pour stocker le nombre de chaînes qui passent par chaque arête. 


**Description des jeux d'essais** 
pour chaque main les tests qui peuvent

Le fichier ChaineMain.c à pour but d'appliquer l'ensemble des fonctions écrites précédement en fonction du choix de l'utilisateur. 
Exemple d'utilisation : ./ChaineMain nom_fichier.cha 
Dans le répertoire de l'utilisateur 

# NOAH !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

**Analyse commentée des performances de nos programmmes***

