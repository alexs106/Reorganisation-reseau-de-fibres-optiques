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


**Description schématique des algorithmes que nous avons crées**


**Réponses aux questions**

**_Exercice 4, question 2_**
Suite à notre test sur les points (x,y) avec *x* un entier allant de 1 à 10 et *y* un entier allant de 1 à 10, nous constatons que plusieurs cléfs ont la même valeurs, soit 88 cléfs sur 100 sont répétées au moins une fois sur notre test.  
De ce fait, la fonction *cle (x,y)* nous semble pas appropriée car elle peut engendrer plusieurs collisions. 
L'unicité de la cléf de hachage est essentielle pour diminuer les problèmes de collisions. 

***Exercice 6, question 1***

***Exercice 6, question 4***

***Exercice 7, question 5***

**Description des jeux d'essais**

**Analyse commentée des performances de nos programmmes***

Temps de calcul pour le fichier 00014_burma.cha
Liste chainée : 0.000016 secondes
Table de Hachage de taille 10 : 0.000019 secondes
Arbre quaternaire : 0.000028 secondes

Temps de calcul pour le fichier 05000_USA-road-d-NY.cha
Liste chainée : 41.933611 secondes
Table de Hachage de taille 100 : 44.075463 secondes
Arbre quaternaire : 0.975671 secondes

Temps de calcul pour le fichier 07397_pla.cha
Liste chainée : 26.439907 secondes
Table de Hachage de taille 100 : 23.043768 secondes
Arbre quaternaire : 0.116468 secondes

Temps de calcul pour le fichier 00014_burma.cha
Liste chainée : 0.000060 secondes
Table de Hachage de taille 100 : 0.000060 secondes
Arbre quaternaire : 0.000051 secondes
