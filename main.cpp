#include <vector>
#include "Population.h"
#include <random>

std::vector<int[2]> generer_villes(int n, int vmax)
{
    bool est_dedans;
    int i;
    int x, y;
    std::vector<int[2]> villes;
    int ville[2];

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, vmax);// TODO: vérifer borne

    while (villes.size() < n)
    {
        x = dis(gen);
        y = dis(gen);
        ville[0] = x;
        ville[1] = y;
        est_dedans = false;
        for (i = 0; i < villes.size(); i++)
        {
            if (villes[i][0] == x and villes[i][1] == y)
            {
                est_dedans = true;
            }
        }
        if (not(est_dedans))
        {
            villes.push_back(ville);
        }
    }
    return villes;
}


std::vector<std::vector<double>> calculer_distance(std::vector<int[2]> villes, int origine[2])
{
    //
}


int main()
{
    int origine[2] = {0, 0};
    std::vector<std::vector<double>> M = calculer_distance(generer_villes(25, 30), origine);
    return EXIT_SUCCESS;
}
