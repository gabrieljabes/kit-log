#pragma once
#include "OneTree.h"

struct Node{
    vector<pair<int, int>> forbidden_edges;
    vector<double> lambda;
    OneTree tree;
    int choosen;

    bool operator<(const Node& outro) const{
        return tree.LB < outro.tree.LB;
    }

    bool operator>(const Node& outro) const{
        return tree.LB > outro.tree.LB;
    }

};

void updateNode(Node& node, double& ub, vector<vector<double>>& custos);