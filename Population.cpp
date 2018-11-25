#include "Population.h"


Population::Population(int taille)
{
    int i;
    this->taille_population = taille;
    for (i = 0; i < this->taille_population; i++)
    {
        this->individus.push_back(Individus(this->M));
    }
}


bool trier_individus(Individus i, Individus j)
{
    return i.recuperer_score() < j.recuperer_score();
}


void Population::decimer(double fraction)
{
    std::sort(this->individus.begin(), this->individus.end(), trier_individus);
    while(this->individus.size() > (this->taille_population * fraction / 100) )
    {
        this->individus.pop_back();
    }
}


void Population::muter(double probabilite)
{
    int i;
    std::sort(this->individus.begin(), this->individus.end(), trier_individus);
    for (i = 5; i < individus.size(); i++)
    {
        if (true)
        {
            this->individus[i].muter();
        }
    }
}


void Population::renouveler()
{
    int i;
    for (i = 0; i < this->taille_population; i++)
    {
        this->individus.push_back(this->individus[i].croiser(this->individus[i+1]));
    }
}