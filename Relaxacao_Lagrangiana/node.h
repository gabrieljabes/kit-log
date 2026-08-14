#pragma once
#include "subtours.h"

struct Node{
    vector<pair<int, int>> forbidden_arcs;
    vector<vector<int>> subtours;
    double lower_bound;
    int choosen;
    bool feasible;

    bool operator<(const Node& outro) const{
        return lower_bound < outro.lower_bound;
    }

    bool operator>(const Node& outro) const{
        return lower_bound > outro.lower_bound;
    }

};

void updateNode(Node *node, Data& problem_info);