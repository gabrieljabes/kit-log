#include <iostream>
using namespace std;

#include "Data.h"
#include "hungarian.h"
#include <vector>
#include <algorithm>

vector<int> Subtour(hungarian_problem_t& p, int i, Data& data, vector<int>& visitados);
vector<vector<int>> All_Subtour(hungarian_problem_t& p, Data& data);

int main(int argc, char** argv) {

	Data data = Data(argc, argv[1]);
	data.read();

	size_t n = data.getDimension();

	double **cost = new double*[n];
	for (int i = 0; i < n; i++){
		cost[i] = new double[n];
		for (int j = 0; j < n; j++){
			cost[i][j] = data.getDistance(i+1,j+1);
		}
	}

	hungarian_problem_t p;
	int mode = HUNGARIAN_MODE_MINIMIZE_COST;
	hungarian_init(&p, cost, n, n, mode); // Carregando o problema

	double obj_value = hungarian_solve(&p);
	cout << "Obj. value: " << obj_value << endl;

	cout << "Assignment" << endl;
	hungarian_print_assignment(&p);


	vector <vector<int>> subtours = All_Subtour(p, data);
	
	for(int i = 0; i < subtours.size(); i++){
		for(int j = 0; j < subtours[i].size(); j++){
			cout << subtours[i][j] << ", ";
		}
		cout << endl;
	}

	hungarian_free(&p);
	for (int i = 0; i < n; i++) delete [] cost[i];
	delete [] cost;

	return 0;
}

vector <int> Subtour(hungarian_problem_t& p, int i, Data& data, vector<bool>& visitados){
	vector <int> subtour;
		int i_save = i;
	do{
		for(int j = 0; j < data.getDimension(); j++){
			if(p.assignment[i][j] == 1){
				if(subtour.empty()){
					subtour.push_back(i+1);
				}
				subtour.push_back(j+1);
				visitados[j] = true;
				i = j;
				break;
			}
		}
	}while(i_save != i);

	return subtour;
}

vector<vector<int>> All_Subtour(hungarian_problem_t& p, Data& data){
	vector<vector<int>> all_s;
	vector<bool> visitados(data.getDimension(), false);
	
		for(int i = 0; i < data.getDimension(); i++){
			if(visitados[i])
				continue;
			else{
				all_s.push_back(Subtour(p, i, data, visitados));
			}
		}

	cout << endl;
	return all_s;
}