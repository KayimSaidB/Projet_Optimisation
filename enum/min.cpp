#include "min.hh"

using namespace std;

Min::Min():nb_cont(0), nb_var(0), fonction_cout(0,0.0), contrainte_gauche(0), contrainte_droite(0,0.0)
{}

Min::Min(int m, int n):nb_cont(m), nb_var(n), fonction_cout(n,0.0), contrainte_gauche(m), contrainte_droite(m,0.0)
{
	for(int i = 0; i < m ; ++i)
	{
		contrainte_gauche[i].resize(n);
	}
}

Min::Min(const Min &obj)
{
	nb_cont = obj.nb_cont;
	nb_var = obj.nb_var;
	var_lb = obj.var_lb;
	var_ub = obj.var_ub;
	out_val = obj.out_val;

	fonction_cout = obj.fonction_cout;
	contrainte_gauche = obj.contrainte_gauche;
	contrainte_droite = obj.contrainte_droite;
}


Min::Min(std::string file_name)
{
	
	ifstream file(file_name);
	std::string line;

	while(getline(file,line))
	{
		if(line.find("Nbr of variables")!= std::string::npos)
		{
			nb_var = stoi(line.substr(line.size()-2));

			getline(file,line);
			line.erase(remove(line.begin(), line.end(),' '),line.end());
			var_lb = stod(line.substr(line.size()-10));

			getline(file,line);
			line.erase(remove(line.begin(), line.end(),' '),line.end());
			var_ub = stod(line.substr(line.size()-10));
			getline(file,line);
			getline(file,line);
			getline(file,line);

			nb_cont = stoi(line.substr(line.size()-8));
			// cout <<out_val<<endl;
		}

		if(line.find("Objective coefficients")!= std::string::npos)
		{
			getline(file,line);
			for(int i = 0; i<nb_var; ++i)
			{
				getline(file,line);
				line = line.substr(7);
				line.erase(remove(line.begin(), line.end(),' '),line.end());
				fonction_cout.push_back(stod(line));
			}

			getline(file,line);
			getline(file,line);
			getline(file,line);
			std::vector<double> b_tmp;
			for(int i = 0; i<nb_var*nb_cont; ++i)
			{
				getline(file,line);
				line = line.substr(7);
				line.erase(remove(line.begin(), line.end(),' '),line.end());
				b_tmp.push_back(stod(line));
			}

			getline(file,line);
			getline(file,line);
			getline(file,line);
			std::vector< std::pair<double,double> > tmp;
			for(int i = 0; i<nb_cont; ++i)
			{
				tmp.clear();
				for(int j = i*nb_var; j<(i+1)*nb_var; ++j)
				{
					getline(file,line);
					line = line.substr(7);
					line.erase(remove(line.begin(), line.end(),' '),line.end());
					tmp.push_back(std::make_pair(b_tmp[j],stod(line)));
				}
				contrainte_gauche.push_back(tmp);
			}

			getline(file,line);
			getline(file,line);
			getline(file,line);
			for(int i = 0; i<nb_cont; ++i)
			{
				getline(file,line);
				line = line.substr(7);
				line.erase(remove(line.begin(), line.end(),' '),line.end());
				contrainte_droite.push_back(stod(line));
			}
		}

	}
	out_val = 0;
	file.close();
	// first = true;
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
			if(j==indice_max()) continue;
			sum += contrainte_gauche[i][j].first;
		}
		if(sum > contrainte_droite[i]) return false;
	}

	return true;
}

void Min::set_cont_droite(int val)
{
	for(int i = 0; i < nb_cont; ++i)
	{
		contrainte_droite[i] -= contrainte_gauche[i][indice_max()].first * pow(contrainte_gauche[i][indice_max()].second,val);
	}
}

void Min::set_out_val(int val)
{
	out_val = fonction_cout[indice_max()] * val;
}


void Min::print(ostream &flux)
{
	string s = "";

	if(out_val == 0.0 && first)
	{
		first = false;
		s += "Min ";
		for(int i = 0; i <nb_var-1; ++i)
		{
			s+= to_string(fonction_cout[i]) + "X" + to_string(i) + " + ";
		}
		s+= to_string(fonction_cout[nb_var-1]) + "X" + to_string(nb_var-1);
	}
	else
	{
		s+=to_string(out_val);
		s += " + Min ";
		for(int i = 0; i <nb_var-1; ++i)
		{
			if(i==indice_max()) continue;
			s+= to_string(fonction_cout[i]) + "X" + to_string(i) + " + ";
		}
		s+= to_string(fonction_cout[nb_var-1]) + "X" + to_string(nb_var-1);
	}

	s += "\n \ncond. ";
	for(int i = 0; i < nb_cont; ++i)
	{
		for(int j = 0; j<nb_var; j++)
		{
			if(j==indice_max()) continue;
			s+= to_string(contrainte_gauche[i][j].first) + "*" + to_string(contrainte_gauche[i][j].second) + "^X" + to_string(j) + " + ";
		}
		s+= "<= " + to_string(contrainte_droite[i]);
		s+= "\n\n\n";
	}
	flux <<s<<endl;
}