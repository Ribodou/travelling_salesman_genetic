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
 
//Les includes:
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

//définitions des fonctions
void generer_villes(int n, int vmax, int villes[][2])
{
    int x;
    int y;
    int i;
    int j;
    int est_dedans_liste;
    for (i = 0; i<n; i++)
    {
        do
        {
            
            x = rand()%(vmax+1);
            y = rand()%(vmax+1);
            est_dedans_liste = 0;//Je ne connais pas les booléens :(
            for (j = 0;j<i;j++)
            {
                if ((villes[j][0] == x) && (villes[j][1] == y))
                {
                    est_dedans_liste = 1;
                }
            }
        }while (est_dedans_liste == 1);
        villes[i][0] = x;
        villes[i][1] = y;
    }
}

void afficher_ville(int n, int villes[][2])
{
    int i;
    for (i=0;i<n;i++){
        printf("La ligne %d de villes contient:%d,%d\n",i,villes[i][0],villes[i][1]);
    }
}

int est_dedans(int n, int taille_liste, int liste[])
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

void normaliser_chemin(int taille_chemin, int chemin[], int n)
{
    int normal[taille_chemin];
    int i;
    int indice=0;
    for (i=0;i<n;i++)
    {
        normal[i] = n+1;
    }
    for (i=0;i<n;i++)
    {
        if ( (chemin[i]<n) && (est_dedans(i,n,normal) == 0) )
        {
            normal[indice] = chemin[i];
            indice = indice + 1;
        }
    }
    for (i=0;i<n;i++)
    {
        if ((est_dedans(i,n,normal)==0))
        {
            normal[indice] = i;
            indice = indice + 1;
        }
    }
    for (i=0;i<n;i++)
    {
        chemin[i] = normal[i];
    }
}

float distance(int pts[][2], int i, int j)
{
    return sqrt( (pts[i][0]-pts[j][0])*(pts[i][0]-pts[j][0]*1.0) + (pts[i][1]-pts[j][1])*(pts[i][1]-pts[j][1])*1.0 );
}

float longueur_chemin(int taille_chemin,int matrice_distances[][taille_chemin], int chemin[])
{
    float s = matrice_distances[taille_chemin][chemin[0]];
    int i;
    for (i=0;i<taille_chemin-1;i++)
    {
        s = s+ matrice_distances[chemin[i]][chemin[i+1]];
    }
    return s;
    
}

void calculer_distances(int x, int y, int n, int villes[][n],float d[][n+1])
{
    int i;
    int j;
    for (i=0;i<n+1;i++)
    {
        for (j=0;j<n+1;j++)
        {
            if (i<n)
            {
                if (j<n)
                {
                    d[j][i] = distance(villes,i,j);
                }
                else
                {
                    d[j][i] = sqrt( (villes[i][0]-x)*(villes[i][0]-x)*1.0 + (villes[i][1]-y)*(villes[i][1]-y)*1.0 );
                }
            }
            else
            {
                if (j<n)
                {
                    d[j][i] = sqrt( (x-villes[j][0])*(x-villes[j][0])*1.0 + (y-villes[j][1])*(y-villes[j][1])*1.0 );
                }
                else
                {
                    d[j][i] = 0;
                }
            }
        }
    }
}
// FIN

//THIS PART IS STILLE UNDER CONSTRUCTION
void creer_population(int n, int n_pop, float d[][n], int population[][n])
{
    
}
/*code python a passer en c
 def creer_population(m,d):
    population = []
    k = len(d)-1#nombre de points
    L = [i for i in range(k)]#liste des points
    for i in range(m):
        N = L[:]
        chemin = []
        while len(N) > 0:
            j = rd.randint(0,len(N)-1)
            chemin.append(N.pop(j))
        population.append((chemin, longueur_chemin(chemin,d)))
    return population
*/


void interclassement(int i, int j, int k, float T[])
{
    int r;
    float S[k-i];
    for (r = i; r < k; r++)
    {
        S[r] = T[r];
    }
    for (r=k+1; r<j;r++)
    {
        S[r] = T[j-r+k+1];
    }
    int d = i;
    int f = j;
    int s;
    for (s=i;s<j;s++)//PB?
    {
        if (S[d] < S[f])
        {
            T[s] = S[d];
            d++;
        }
        else
        {
            T[s] = S[f];
            f--;
        }
    }
}
        
void tri_fusion(int i, int j, float liste[])
{
    int k;
    if (i<j)
    {
        k = floor((i*1.0+j*1.0)/2);
        tri_fusion(i,k,liste);
        tri_fusion(k+1,j,liste);
        interclassement(i,j,k,liste);
    }
}





//corps du programme principal

int main(){
    // MODIFY THIS LINE IF YOU YOU WANT TO USE A FILE
    int source_fichier =0;
    
    //definitions des paramètres
    int n = 32;
    int n_pop = 500;
    int vmax = 25;
    int villes[n][2];
    int chemins[500];
    int scores[500];
    int x,y;//coordonnées de départ
    
    x = 0;
    y = 0;
    
    //aléatoire
    srand(time(NULL));
    
    //on va remplir villes
    if (source_fichier == 0)
    {
        generer_villes(n,vmax,villes);//on peut aussi les lire
    }
    //afficher_ville(n,villes);
    
    //test de l'algorithme de tris
    float l[100];
    
    for (x = 0;x<100;x++)
    {
        l[x] = rand()*1.0;
    }
    
    // on sépare l'affichage
    for (x=0;x<5;x++)
    {
        printf("\n");
    }
    
    //on trie et on affiche le résultat
    tri_fusion(0,100,l);
    for (x = 0;x<100;x++)
    {
        printf("%f\n",l[x]);
    }
    return EXIT_SUCCESS;
}
