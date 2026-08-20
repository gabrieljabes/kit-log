#pragma once
#include "Kruskal.h"
#include "Data.h"
#include <bits/stdc++.h>

struct OneTree{
    vii edges;
    vector<int> degree;
    double LB = 0;
    bool is_tour = false;
};

OneTree solve1Tree(Data& tsp_info, vector<double>& lambda);
OneTree SubgradientMethod(double& ub, Data& tsp_info);
