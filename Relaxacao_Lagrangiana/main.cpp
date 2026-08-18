#include <bits/stdc++.h>
#include "Kruskal.h"
#include "OneTree.h"

using namespace std;


int main(){

    int m;
    m = 5;
    double ub = 148.0;
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
        lambda[i] = 0.0;

    OneTree t = SubgradientMethod(ub, custos);

    return 0;
}

