#include <bits/stdc++.h>
#include "Kruskal.h"
#include "OneTree.h"
#include "Data.h"
#include "node.h"
#include "branchingStrategy.h"

using namespace std;

OneTree runDFS_BFS(Node& root, double& upper_bound, string& strategy, vector<vector<double>>& custos_linha);

int main(int argc, char** argv) {  
   
    srand(time(NULL));
    
    auto data = Data(argc, argv[1]);
    data.read();
    size_t n = data.getDimension(); 

    cout << "Dimension: " << n << endl;
    cout << "DistanceMatrix: " << endl;
    data.printMatrixDist(); 

    double ub = stod(argv[2]);
    vector<vector<double>> custo(n, vector<double>(n));
    
        for(int i = 0; i < n; i++){
            for(int j = i + 1; j < n; j++){
                custo[i][j] = data.getDistance(i + 1, j + 1);
                custo[j][i] = custo[i][j];
            }
        }
    Node root;
    string bfs = "BFS";
    string dfs = "DFS";
    OneTree best_tree = runDFS_BFS(root, ub, bfs, custo); 

    return 0;
}   

OneTree runDFS_BFS(Node& root, double& upper_bound, string& strategy, vector<vector<double>>& custos_linha){

	list<Node> node_tree;
    OneTree best_tree;
    int n = custos_linha.size();

    root.lambda = vector<double>(n, 0);
	node_tree.push_back(root);

	while(!node_tree.empty()){
		auto node = DFS_or_BFS(strategy, node_tree);
        updateNode(node, upper_bound, custos_linha);

        cout << "LB=" << node.tree.LB << " ub=" << upper_bound
            << " tour=" << node.tree.is_tour
            << " proib=" << node.forbidden_edges.size()
            << " fila=" << node_tree.size() << endl;
            
        //poda
        if(node.tree.LB >= upper_bound)
            continue;

        if(node.tree.is_tour){
            upper_bound = node.tree.LB;
            best_tree = node.tree;
            continue;   
        }
            

        for(auto& k : node.tree.edges){
            if(k.first == node.choosen || k.second == node.choosen){
                Node filho;
                //herda dos pais
                filho.forbidden_edges = node.forbidden_edges;
                //adiciona um forbidden edge
                filho.forbidden_edges.push_back(k);
                filho.lambda = node.lambda;
                node_tree.push_back(filho);
            }
        }
	}

    return best_tree;
}
