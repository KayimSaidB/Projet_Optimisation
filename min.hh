#pragma once

#include <vector>

class Min
{
public:
	Min();
	Min(int m, int n); // m nombre de contraintes, n nombre de variables
	~Min();

private:
	int nb_cont; // nombre de contrainte
	int nb_var; // nombre de variable

	std::vector<double> fonction_cout;
	std::vector<std::vector<double>> contrainte_gauche; // partie gauche de la contrainte
	std::vector<double> contrainte_droite; // partie droite de la contrainte
};