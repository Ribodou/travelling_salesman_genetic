#ifndef __POPULATION_H__
#define __POPULATION_H__

#include <list>
#include <vector>
#include "Individus.h"


class Population {
	private:
		std::vector<std::vector<double>> M;
		int taille_population;
		std::vector<Individus> individus;
	public:
		Population(int taille);
		~Population();

		void decimer(double fractions);
		void muter(double probabilite);
		void renouveler();
};
#endif

