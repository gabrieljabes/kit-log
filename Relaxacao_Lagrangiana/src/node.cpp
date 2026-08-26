#include "node.h"


void updateNode(Node& node, double& ub, vector<vector<double>>& custos){
    int dim = custos.size();
    vector<vector<double>> custos_linha = custos;

    for(auto& k : node.forbidden_edges){
        int i = k.first;
        int j = k.second;
        custos_linha[i][j] = 99999999;
        custos_linha[j][i] = 99999999;
    }

    node.tree = SubgradientMethod(ub, node.lambda, custos_linha);

    int max_degree = 0;
    int max_degree_i = -1;
    for(int i = 0; i < node.tree.degree.size(); i++){
        if(node.tree.degree[i] >= max_degree){
            max_degree = node.tree.degree[i];
            max_degree_i = i;
        }   
    }
    node.choosen = max_degree_i;
}   