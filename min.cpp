#include "min.hh"

Min::Min():nb_cont(0), nb_var(0), fonction_cout(0,0.0), contrainte_gauche(0), contrainte_droite(0,0.0)
{}

Min::Min(int m, int n):nb_cont(m), nb_var(n), fonction_cout(n,0.0), contrainte_gauche(m), contrainte_droite(m,0.0)
{
	for(int i = 0; i < m ; ++i)
	{
		contrainte_gauche[i].resize(n,0);
	}
}

Min::~Min()
{}