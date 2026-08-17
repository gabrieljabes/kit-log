#pragma once
#include "Kruskal.h"
#include <bits/stdc++.h>

struct OneTree{
    vii edges;
    vector<int> degree;
    double LB;
    bool is_tour;
};

OneTree solve1Tree(vector<vector<double>>& costs, vector<double>& lambda);
