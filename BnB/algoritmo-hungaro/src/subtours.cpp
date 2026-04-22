#include "subtours.h"

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

vector<int> min_subtour(vector<vector<int>>& all_subtour){
	size_t best_qtd = INT_MAX;
	int best_i;
	for(int i = 0; i < all_subtour.size(); i++){
		if(best_qtd > all_subtour[i].size()){
			best_qtd = all_subtour[i].size();
			best_i = i;
		}
	}	

	return all_subtour[best_i];
}