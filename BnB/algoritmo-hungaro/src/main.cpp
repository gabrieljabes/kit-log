#include <iostream>
using namespace std;

#include "Data.h"
#include "hungarian.h"
#include "subtours.h"
#include "node.h"
#include "branchingStrategy.h"
#include <vector>
#include <algorithm>
#include <climits>
#include <list>


int main(int argc, char** argv) {

	Data data = Data(argc, argv[1]);
	data.read();

	size_t n = data.getDimension();

	Node root;
	updateNode(&root, data);

	list<Node> tree;
	tree.push_back(root);

	double upper_bound = stod(argv[2]) + 1;
	vector <int> best_s;

	while(!tree.empty()){
		auto node = strategyDFS(tree);

		if(node.feasible){
			if(node.lower_bound < upper_bound){
				upper_bound = node.lower_bound;
				best_s = node.subtours[0];
			}
			continue;	
		}
	
		for(int i = 0; i < node.subtours[node.choosen].size() - 1; i++){
			Node n;
			n.forbidden_arcs = node.forbidden_arcs;

			pair<int, int> forbidden_arc;
			//os subtours tem nodes a partir de 1
			forbidden_arc.first = node.subtours[node.choosen][i] - 1;
			forbidden_arc.second = node.subtours[node.choosen][i+1] - 1;

			n.forbidden_arcs.push_back(forbidden_arc);
			updateNode(&n, data);
			if(n.lower_bound <= upper_bound)
				tree.push_back(n);	
		}
	}

	for(auto& i : best_s)
		cout << i << ", ";
	cout << endl;


	return 0;
}
