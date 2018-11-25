#ifndef __INDIVIDUS_H__
#define __INDIVIDUS_H__


#include <vector>
#include <algorithm>


class Individus {
	private:
		std::vector<std::vector<double> > M;
		std::vector<int> genes;
		double score;
	public:
		Individus(std::vector<std::vector<double> > _M);
		Individus(std::vector<std::vector<double> > _M, std::vector<int> _genes);
		double recuperer_score();
		void calculer_score();
		void normaliser();
		void muter();
		Individus croiser(const Individus &other);
};

#endif

