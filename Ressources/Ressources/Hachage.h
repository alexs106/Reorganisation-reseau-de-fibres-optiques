#ifndef __HACHAGE_H__
#define __HACHAGE_H__
#include "Reseau.h"

typedef struct{
  int nbElement; //pas necessaire ici
  int tailleMax;
  CellNoeud** T;
}TableHachage;

TableHachage* creation_table_hachage(int tailleM);
int cle(double x,double y); 
int hachage(int cle, TableHachage *h); 
Noeud* rechercheCreeNoeudHachage(Reseau* R, TableHachage* H, double x, double y);
Reseau* reconstitueReseauHachage(Chaines *C, int M);
void liberation_hachage(TableHachage* TableH); 
#endif