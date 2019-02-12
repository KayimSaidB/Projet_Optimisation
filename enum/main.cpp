#include "min.hh"
#include "tree_util.hh"
#include <stdio.h>
#include <fstream>
#include <iostream>
#include <numeric>
#include <cmath> 
using namespace std; 

string to_string(Min &probleme)
{
	string s = "";

	if(probleme.out_val == 0.0 && probleme.first)
	{
		probleme.first = false;
		s += "Min ";
		for(int i = 0; i <probleme.nb_var-1; ++i)
		{
			s+= to_string(probleme.fonction_cout[i]) + "X" + to_string(i) + " + ";
		}
		s+= to_string(probleme.fonction_cout[probleme.nb_var-1]) + "X" + to_string(probleme.nb_var-1);
	}
	else
	{
		s+=to_string(probleme.out_val);
		s += " + Min ";
		for(int i = 0; i <probleme.nb_var-1; ++i)
		{
			if(i==probleme.indice_max()) continue;
			s+= to_string(probleme.fonction_cout[i]) + "X" + to_string(i) + " + ";
		}
		s+= to_string(probleme.fonction_cout[probleme.nb_var-1]) + "X" + to_string(probleme.nb_var-1);
	}

	s += "\ncond. ";
	for(int i = 0; i < probleme.nb_cont; ++i)
	{
		for(int j = 0; j<probleme.nb_var; j++)
		{
			if(j==probleme.indice_max()) continue;
			s+= to_string(probleme.contrainte_gauche[i][j].first) + "*" + to_string(probleme.contrainte_gauche[i][j].second) + "^X" + to_string(j) + " + ";
		}
		s+= "<= " + to_string(probleme.contrainte_droite[i]);
	}

	return s;
}


tree<Min> create_tree(std::string file_name)
{
	tree<Min> tr;

	Min probleme = Min(file_name);
	// cout << to_string(probleme);
	tree<Min>::iterator it,one,two;
	// it = tr.begin();
	it = tr.insert(tr.begin(),probleme);
	// two = tr.append_child(one,probleme);

	// cout << tr.number_of_children(one);

	// kptree::print_tree_bracketed(tr,cout);


	Min tmp;
	Min tmp2;
	for(int i = 0; i<probleme.var_ub+1; i++)
	{
		cout<<""<<endl;
		tmp = probleme;
		tmp.first = false;
		tmp.set_cont_droite(i);
		tmp.set_out_val(i);
		tmp2 = tmp;
		two = tr.append_child(it,tmp);
	}

	for(int i = 0; i<probleme.var_ub+1; i++)
	{

		cout<<""<<endl;
		tmp= tmp2;
		tmp.first = false;
		tmp.set_cont_droite(i);
		tmp.set_out_val(i);
		tr.append_child(two,tmp);
	}

	cout << tr.number_of_children(two);
	// kptree::print_tree_bracketed(tr,cout);
	return tr;
}


void export_dot(tree<Min>& arbre)
{

	tree<Min>::breadth_first_iterator it;

	it = arbre.begin();

	// cout << *it<<endl;
	ofstream file("enum.dot");
	string s="";
	s += "digraph L {\n";

	s+= "0[label=\"";
	s+= to_string(*it);
	// int indice_max = it.data.indice_max();
	s+= "\"]\n";

	bool first = true;
	int i = 1;
	while(it!=arbre.end())
	{
		if(first) { first = false; it ++; continue;}
		s+= to_string(i) + "[label=\"";
		s+= to_string(*it);
		s+= "\"]\n";
		i++;
		if(i<4)
		{
			it++;
		}
		else break;
	}

	for(int i = 1; i<4; i++) s+= "0->" + to_string(i) + "[label=\"X" + to_string(0) + "= " + to_string(i-1) + "\"]\n";


	file<<s;
	file<<"\n}";
}



int main(){

	std::cout.precision(10);

	tree<Min> arbre = create_tree("Data/expknap-15-3.nkp");
	export_dot(arbre);
}