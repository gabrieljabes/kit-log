#include <bits/stdc++.h>
#include "Kruskal.h"
#include "OneTree.h"
#include "Data.h"
#include "node.h"
#include "branchingStrategy.h"

using namespace std;

OneTree runDFS_BFS(Node& root, double& upper_bound, string& strategy, vector<vector<double>>& custos_linha);
OneTree runBBS(Node& root, double& upper_bound, string& strategy, vector<vector<double>>& custos_linha);


/*  bnb benchmark 
            bfs         dfs         bbs
bayg29	    0,15247	    0,142791	0,18136     1610
bays29	    0,488737	0,461586	0,561069    2020
burma14	    0,352039	0,331064	0,392897    3323
fri26	    2,3009	    2,02871	    2,7424      937
gr17	    41.62	    34,6609	    51,4811     2085
gr21	    0,00098497	0,00096842	0,0010375   2707
gr24	    0,0745536	0,0660434	0,085498    1272
ulysses16	7,22943	    6,44595	    8,20949     6859
*/
int main(int argc, char** argv) {  
   
    srand(time(NULL));
    
    auto data = Data(argc, argv[1]);
    data.read();
    size_t n = data.getDimension(); 

    cout << "Dimension: " << n << endl;
    cout << "DistanceMatrix: " << endl;
    data.printMatrixDist(); 

    double ub = stod(argv[2]) + 1; 
    vector<vector<double>> custo(n, vector<double>(n));
    
        for(int i = 0; i < n; i++){
            for(int j = i + 1; j < n; j++){
                custo[i][j] = data.getDistance(i + 1, j + 1);
                custo[j][i] = custo[i][j];
            }
        }
    Node root;
    string strategy = (argv[3]);

    auto t1 = chrono::high_resolution_clock::now();
    OneTree best_tree;

    if(strategy == "BBS")
        best_tree = runBBS(root, ub, strategy, custo); 
    else{
        best_tree = runDFS_BFS(root, ub, strategy, custo);
    }

    auto t2 = chrono::high_resolution_clock::now();
	double tempo = chrono::duration<double>(t2 - t1).count();

    cout << "lb = " << best_tree.LB << endl;
    cout << tempo << endl;

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

OneTree runBBS(Node& root, double& upper_bound, string& strategy, vector<vector<double>>& custos_linha){
	priority_queue<Node, vector<Node>, greater<Node>> node_tree;
	OneTree best_tree;
    int n = custos_linha.size();

    root.lambda = vector<double>(n, 0);
	node_tree.push(root);

	while(!node_tree.empty()){
		auto node = strategyBBS(node_tree);
        updateNode(node, upper_bound, custos_linha);

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
                node_tree.push(filho);
            }
        }
	}

    return best_tree;
}
