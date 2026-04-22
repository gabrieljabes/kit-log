#include <iostream>
using namespace std;

#include "Data.h"
#include "hungarian.h"
#include "subtours.h"
#include <vector>
#include <algorithm>
#include <climits>


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

	vector<int> s = min_subtour(subtours);

	for(int i = 0; i < s.size(); i++){
			cout << s[i] << ", ";
		}

	hungarian_free(&p);
	for (int i = 0; i < n; i++) delete [] cost[i];
	delete [] cost;

	return 0;
}
