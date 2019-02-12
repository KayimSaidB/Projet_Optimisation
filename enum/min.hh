#pragma once

#include <vector>
#include <utility>
#include "algorithm"
#include <math.h>
#include <fstream>
#include <iostream>

class Min
{
public:
	Min();
	Min(int m, int n); // m nombre de contraintes, n nombre de variables
	Min(const Min &obj);
	Min(std::string file_name);
	~Min();


	int indice_max(); // retourne l'indice de la variable à minimiser
	int indice_min();
	bool isSatisfy(); // regarde si tous les contraintes sont satisfaites
	void set_out_val(int val);
	void set_cont_droite(int val);
	void print(std::ostream &flux);

	double var_lb; 
	double var_ub;
	bool first;
public:
	int nb_cont; // nombre de contrainte
	int nb_var; // nombre de variable
	double out_val; // valeur à l'extérieure de la minimisation
	std::vector<double> fonction_cout;
	std::vector< std::vector< std::pair<double,double> > > contrainte_gauche; // partie gauche de la contrainte
	std::vector<double> contrainte_droite; // partie droite de la contrainte
};