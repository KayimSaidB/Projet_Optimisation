#include <stdio.h>
#include <fstream>
#include <iostream>
#include <vector> 
#include <numeric>
#include <cmath> 
using namespace std; 
int function(vector<int> x,vector<int>a){

     return inner_product(a.begin(), a.end(), x.begin(), 0.0);


}

bool check_constraints(vector< vector<int> > b, vector<int> c,vector<int> x,vector<int> bound,int m,int n,vector<int> ub,vector<int> lb){
	// m nombre de contraintes et n taille du vecteru
	int j,i;
		for (j=0;j<n;j++) if (x[j]<lb[j] || x[j]>ub[j]) return false;

	for (i=0;i<m;i++){
		int sum=0;
		
	for (j=0;j<n;j++){
		sum=sum+b[i][j]*pow(c[j],-x[j]);

	}
	if (sum>bound[i]) return false;
	}
	

	return true;
}

int main(){
	vector<int> x;
	vector<int> a;	
	a.push_back(1);
	a.push_back(1);
	a.push_back(1);
	x.push_back(1);
	x.push_back(1);
	x.push_back(1);

	   std::cout << "The scalar product is: "
              << function(a,x) <<endl;
}