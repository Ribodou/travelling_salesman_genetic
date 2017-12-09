/* Copyright (C) 2017 Lucas Robidou
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * PS: For any question or any suggestion, please contact me at:
 *luc.robidou@gmail.com
 *
 *  but du programme:
 *determiner, par un algorithme genetique, le meilleur moyen de passer
 *par n points points de passage
 */

#include "travelling_salesman.h"




//corps du programme principal
int main()
{
    // MODIFY THIS LINE IF YOU YOU WANT TO USE A FILE
    int source_fichier =0;

    //definitions des paramètres
    int n = 32;//nombre de ville
    int n_pop = 20;//nombre d'individu dans une population
    int vmax = 25;//coordonee maximale d'une ville
    //double proba = 0.3;//probabilite de mutation
    //int g = 1000;//nombre de génération
    int i;//, j;//compteurs
    double x,y;//coordonnées de départ
    double **d;//matrice représantant la distance entre les villes
    villes *v;
    x = 0;
    y = 0;
    //aléatoire
    srand(time(NULL));

    d = malloc( (n+1) * sizeof(double*));
    for (i=0;i<n+1;i++)
    {
        d[i] = malloc( (n+1) * sizeof(double));
    }

/*
    //on va remplir villes
    if (source_fichier)
    {

    }*/
v= creer_villes(n, vmax);//on peut aussi les lire
    /* Pour commencer, un bel affichage */
    printf("\n\n\n------------------------\n-- debut du programme --\n------------------------\n\n");

    //Création de la population
    //afficher_ville(n,villes);
    calculer_distances(x, y, n, v, d);
    population *pop = creer_population(n, n_pop, d);

    // libéré, délivré...
    for (i=0;i<n;i++)
    {
        free(d[i]);
    }
    free(d);

    return EXIT_SUCCESS;
}







int est_dans_coordonees(villes * vs, double x, double y)
{
	ville *v = vs->tete;
	while(v != NULL)
	{
		if ( (x == v->x) && (y == v->y) )
        {
			return 1;
		}
		v = v->suivante;
	}
	return 0;
}



villes *creer_villes(int n, int vmax)
{
    int i;
	villes * vs = malloc(sizeof(villes));
	ville * v = malloc(sizeof(ville));
	double x, y;

	vs->taille = n;
	vs->tete = v;

	v->x = rand()%(vmax+1);
	v->y = rand()%(vmax+1);
    v->suivante = NULL;

	for (i=0;i<(n-1);i++)
	{
		do
		{
			x = rand()%(vmax+1);
			y = rand()%(vmax+1);
		}while (est_dans_coordonees(vs, x, y) == 1);

		ville *ville_suivante = malloc(sizeof(ville));
		ville_suivante->x = x;
		ville_suivante->y = y;
        ville_suivante->suivante = NULL;

		v->suivante = ville_suivante;
        v = ville_suivante;
    }

    vs->queue = v;

	return vs;
}

void calculer_distances(double x, double y, int n, villes * vs, double **d)
{
    int i;
    int j;
    ville *v1 = vs->tete;
    ville *v2 = vs->tete;
    for (i=0;i<n+1;i++)
    {
        for (j=0;j<n+1;j++)
        {
            if (i==j)
            {
                d[i][j] =0;
            }
            else
            {
                if (i<n)
                {
                    if (j<n)
                    {
                        d[j][i] = sqrt( pow((v1->x - v2->x),2) + pow((v1->y - v2->y),2) );
                    }
                    else
                    {
                        d[j][i] = sqrt( pow((v1->x - x),2) + pow((v1->y - y),2) );
                    }
                }
                else //i>=n (<=> i = n) and j =/= i ( <=> j =/= n <=> j<n (ouf! ) )
                {
                    d[j][i] = sqrt( pow((x - v2->x),2) + pow((y - v2->y),2) );
                }
            }
            if (v2->suivante != NULL)
            {
                v2 = v2->suivante;
            }
        }
        if (v1->suivante != NULL)
        {
            v1 = v1->suivante;
        }
    }
}




population *creer_population(int n, int n_pop, double ** d)
{
    int i;
    population * pop = malloc(sizeof(population));
    pop->taille = n_pop;
    individu *ind = creer_individu(n, d);
    pop->tete = ind;
    for (i=0;i<(n-1);i++)
    {
        individu *ind_suivant = creer_individu(n, d);
        ind->suivant = ind_suivant;
        ind_suivant = ind;
    }
    pop->queue = ind;
    return pop;
}

int est_dedans(int n, int taille_liste, int *liste)
{
    int i;
    int test=0;
    for (i=0;i<taille_liste;i++)
    {
        if (liste[i] == n)
        {
            test = 1;
        }
    }
    return test;
}

double calculer_score(individu *ind, double **d)
{
    int i;
    int n = ind->taille;
    double scores = d[n][ind->gene[0]];
    for (i=0;i<(n-1);i++)
    {
        scores += d[ind->gene[i]][ind->gene[i+1]];
    }
    return scores;
}


individu *creer_individu(int n, double ** d)
{
    int i, k;
    individu *ind  = malloc(sizeof(individu));
    ind->gene = malloc(n*sizeof(int));
    ind->taille = n;
    for (i=0;i<n;i++)
    {
        ind->gene[i] = -1;
    }
    for (i=0;i<n;i++)
    {
        do
        {
            k = random()%n;
        }
        while(est_dedans(k,n,ind->gene)==1);
        ind->gene[i] = k;
    }
    ind->score = calculer_score(ind, d);
    return ind;
}
