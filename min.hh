#pragma once

#include <vector>
#include <utility>
#include "algorithm"
#include <math.h>

class Min
{
public:
	Min();
	Min(int m, int n); // m nombre de contraintes, n nombre de variables
	~Min();

	int indice_max(); // retourne l'indice de la variable à minimiser
	int indice_min();
	bool isSatisfy(); // regarde si tous les contraintes sont satisfaites
private:
	int nb_cont; // nombre de contrainte
	int nb_var; // nombre de variable

	std::vector<double> fonction_cout;
	std::vector< std::vector< std::pair<double,double> > > contrainte_gauche; // partie gauche de la contrainte
	std::vector<double> contrainte_droite; // partie droite de la contrainte
};