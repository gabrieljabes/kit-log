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
#include <queue>
#include <chrono>

void runBBS(Data& problem_info, Node& root, vector<int>& best_s, double& upper_bound);
void runDFS_BFS(Data& problem_info, Node& root, vector<int>& best_s, double& upper_bound, string& strategy);

int main(int argc, char** argv) {

	Data data = Data(argc, argv[1]);
	data.read();

	size_t n = data.getDimension();

	Node root;
	updateNode(&root, data);

	double upper_bound = stod(argv[2]) + 1;
	vector <int> best_s;
	string strategy = argv[3];

	auto t1 = chrono::high_resolution_clock::now();
	if(strategy == "BBS")
		runBBS(data, root, best_s, upper_bound);
	else{
		runDFS_BFS(data, root, best_s, upper_bound, strategy);
	}
	auto t2 = chrono::high_resolution_clock::now();

	double tempo = chrono::duration<double>(t2 - t1).count();
	

	for(auto& i : best_s)
		cout << i << ", ";
	cout << endl;
	cout << " custo: " << upper_bound << endl;
	cout << " tempo: " << tempo << endl;


	return 0;
}

void runBBS(Data& problem_info, Node& root, vector<int>& best_s, double& upper_bound){
	priority_queue<Node> tree;
	tree.push(root);
	while(!tree.empty()){
		auto node = strategyBBS(tree);

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
			updateNode(&n, problem_info);
			if(n.lower_bound <= upper_bound)
				tree.push(n);	
		}
	}

}

void runDFS_BFS(Data& problem_info, Node& root, vector<int>& best_s, double& upper_bound, string& strategy){
	list<Node> tree;
	tree.push_back(root);
	while(!tree.empty()){
		auto node = DFS_or_BFS(strategy, tree);

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
			updateNode(&n, problem_info);
			if(n.lower_bound <= upper_bound)
				tree.push_back(n);	
		}
	}

}