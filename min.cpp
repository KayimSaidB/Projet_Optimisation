#include "min.hh"

Min::Min():nb_cont(0), nb_var(0), fonction_cout(0,0.0), contrainte_gauche(0), contrainte_droite(0,0.0)
{}

Min::Min(int m, int n):nb_cont(m), nb_var(n), fonction_cout(n,0.0), contrainte_gauche(m), contrainte_droite(m,0.0)
{
	for(int i = 0; i < m ; ++i)
	{
		contrainte_gauche[i].resize(n);
	}
}

Min::~Min()
{}

int Min::indice_max()
{
	return std::distance(fonction_cout.begin(), std::max_element(fonction_cout.begin(), fonction_cout.end()));
}

int Min::indice_min()
{
	return std::distance(fonction_cout.begin(), std::min_element(fonction_cout.begin(), fonction_cout.end()));
}

bool Min::isSatisfy()
{
	for(int i = 0; i<nb_cont; ++i)
	{
		double sum = 0;
		for(int j = 0; j<nb_var; ++j)
		{
			sum += contrainte_gauche[i][j].first;
		}
		if(sum > contrainte_droite[i]) return false;
	}

	return true;
}