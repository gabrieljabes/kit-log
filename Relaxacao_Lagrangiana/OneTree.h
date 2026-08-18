#pragma once
#include "Kruskal.h"
#include <bits/stdc++.h>

struct OneTree{
    vii edges;
    vector<int> degree;
    double LB = 0;
    bool is_tour = false;
};

OneTree solve1Tree(vector<vector<double>>& costs, vector<double>& lambda);
OneTree SubgradientMethod(double& ub, vector<vector<double>>& costs);
