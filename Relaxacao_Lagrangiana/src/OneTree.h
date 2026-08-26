#pragma once
#include "Kruskal.h"
#include "Data.h"
#include <bits/stdc++.h>

struct OneTree{
    vii edges;
    vector<int> degree;
    double LB = 0;
    bool is_tour = false;

    bool operator<(const OneTree& outro) const{
    return LB < outro.LB;
    }

    bool operator>(const OneTree& outro) const{
    return LB > outro.LB;
    }
};
OneTree solve1Tree(vector<double>& lambda, vector<vector<double>>& custos_linha);
OneTree SubgradientMethod(double& ub, vector<double>& lambda, vector<vector<double>>& custos_linha);