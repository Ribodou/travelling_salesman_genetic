#include <vector>
#include <algorithm>
#include <random>
// #include <iostream>
#include "Individus.h"


Individus::Individus(std::vector<std::vector<double> > _M) : M(_M)
{
    int i;
    for(i = 0; i < M.size(); i++)
    {
        this->genes.push_back(i);
    }
    random_shuffle(genes.begin(), genes.end());
    this->calculer_score();
}


Individus::Individus(std::vector<std::vector<double> > _M, std::vector<int> _genes) : M(_M), genes(_genes)
{
    this->calculer_score();
}


double Individus::recuperer_score()
{
    return this->score;
}


void Individus::calculer_score()
{
    int i;
    this->score = this->M[this->M.size() - 1][this->genes[0]];
    for (i = 0; i < this->M.size() - 1; i++)
    {
        this->score += this->M[this->genes[i]][this->genes[i + 1]];
    }
}

void Individus::normaliser()
{
    int i, j;
    bool est_dedans = false;
    std::vector<int> nouveaux_genes;
    for (i = 0; i < M.size(); i++)
    {
        if ((0 <= this->genes[i]) and (this->genes[i] <= (M.size() - 1)))
        {
            est_dedans = false;
            for (j = 0; j < nouveaux_genes.size(); j++)
            {
                if (this->genes[i] == nouveaux_genes[j])
                {
                    est_dedans = true;
                }
            }
            if (est_dedans)
            {
                nouveaux_genes.push_back(this->genes[i]);
            }
        }
    }

    for (i = 0; i < M.size(); i++)
    {
        est_dedans = false;
        for (j = 0; j < nouveaux_genes.size(); j++)
        {
            if (nouveaux_genes[j] == i)
            {
                est_dedans = true;
            }
        }
        if (not(est_dedans))
        {
            nouveaux_genes.push_back(i);
        }
    }

    this->genes = nouveaux_genes;
}


void Individus::muter()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, M.size() - 1);

    int i = dis(gen);
    int j = dis(gen);
    // self.genes[i], self.genes[j] = self.genes[j], self.genes[i]
    int temp = this->genes[i];
    this->genes[i] = this->genes[j];
    this->genes[j] = temp;

    this->calculer_score();
}


Individus Individus::croiser(const Individus &other)
{
    int i;
    int moitiee = M.size() / 2;
    std::vector<int> genes_bebe;
    for (i = 0; i < moitiee; i++)
    {
        genes_bebe.push_back(this->genes[i]);
    }
    for (i = moitiee; i < M.size(); i++)
    {
        genes_bebe.push_back(other.genes[i]);
    }
    Individus bebe(M, genes_bebe);
    bebe.normaliser();
    return bebe;
}
