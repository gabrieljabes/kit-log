#include "node.h"

void updateNode(Node *node, Data& problem_info){

    hungarian_problem_t p;

	size_t n = problem_info.getDimension();
	double **cost = new double*[n];

	for (int i = 0; i < n; i++){
		cost[i] = new double[n];
		for (int j = 0; j < n; j++){
			cost[i][j] = problem_info.getDistance(i+1,j+1);
		}
    }

    for(int k = 0; k < node->forbidden_arcs.size(); k++){
        int i = node->forbidden_arcs[k].first;
        int j = node->forbidden_arcs[k].second;

        cost[i][j] = 99999999;
    }

	int mode = HUNGARIAN_MODE_MINIMIZE_COST;
	hungarian_init(&p, cost, n, n, mode);

    node->lower_bound = hungarian_solve(&p);

    node->subtours = All_Subtour(p, problem_info);
    node->choosen = index_min_subtour(node->subtours);
    //se for uma rota de tsp valida so vai existir um subtour   
    node->feasible = (node->subtours.size() == 1);

    for(int i = 0; i < n; i++)
        delete[] cost[i];
    delete[] cost;

    hungarian_free(&p);
}