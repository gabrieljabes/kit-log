#include <bits/stdc++.h>
// #include "subgradient.cpp"
#include "Kruskal.h"
#include "Kruskal.cpp"
#include "OneTree.h"
#include "OneTree.cpp"

using namespace std;

const double epsilon_min = pow(10, -5);
// const double k_max;


int main(){

    int m;
    m = 5;
    vector<double> custos_arbitrarios = {30.0, 26.0, 50.0, 40.0, 24.0, 40.0, 50.0, 24.0, 26.0, 30.0};
    vector<vector <double>> custos(m, vector<double>(m));
    vector<double> lambda (m);

    int k = 0;
    for(int i = 0; i < m; i++){
        for(int j = i + 1; j < m; j++){
            custos[i][j] = custos_arbitrarios[k];
            k++;
        }
    }

    for(int i = 0; i < m; i++)
        lambda[i] = 0;

    OneTree tree = solve1Tree(custos, lambda);

    return 0;
}

