#ifndef TRAVELLING_SALESMAN_H
#define TRAVELLING_SALESMAN_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <assert.h>
#include <stdint.h>

////////////////////////////////////////////////////////////////////////
         //////       ////////////       ////////
     //////////////   ////////////     ////////////
    ////////  ///////     ////         ////     ////
   ////////               ////         ////      ///
   ////////               ////         ////    ////
      //////              ////         //////////
       /////              ////         ////  /////
        //////            ////         ////    ////
///    //////             ////         ////     ////
 ///////////              ////         ////     /////
////////////////////////////////////////////////////////////////////////



typedef struct _individu
{
	int taille;
	int * gene;
	double score;
	struct _individu *suivant;
} individu;

typedef struct
{
	int taille;
	individu *tete;
	individu *queue;
} population;

typedef struct _ville
{
	double x;
	double y;
	struct _ville * suivante;
} ville;

typedef struct
{
	int taille;
	ville *tete;
	ville *queue;
}villes;

////////////////////////////////////////////////////////////////////////
   /////
///// ////
///
///
///
///
///    //
  //////
////////////////////////////////////////////////////////////////////////

//fonction de test pour savoir si (x,y) et dans une ville de villes
int est_dans_coordonees(villes * vs, double x, double y);

//fonction de création des villes
villes *creer_villes(int n, int vmax);

//calcule la matrice d
void calculer_distances(double x, double y, int n, villes * vs, double **d);

//fonction de création de la population initiale
population *creer_population(int n, int n_pop, double ** d);

//teste si n est dans le tableau liste, de taille taille_liste
int est_dedans(int n, int taille_liste, int *liste);

//calcule le score d'un individu
double calculer_score(individu *ind, double **d);

//creer un nouvel individu
individu *creer_individu(int n, double ** d);


#endif
