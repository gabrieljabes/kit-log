#pragma once
#include "subtours.h"

struct Node{
    vector<pair<int, int>> forbidden_arcs;
    vector<vector<int>> subtours;
    double lower_bound;
    int choosen;
    bool feasible;
};

void updateNode(Node *node, Data& problem_info);