#include <bits/stdc++.h>
// #include "subgradient.cpp"
#include "Kruskal.h"
#include "Kruskal.cpp"

using namespace std;

const double epsilon_min = pow(10, -5);
// const double k_max;

void solve1Tree(vector<vector<double>>& costs, vector<double>& lambda);

int main(){

    int m;
    m = 5;
    vector<double> custos_arbitrarios = {30.0, 26.0, 50.0, 40.0, 22.0, 40.0, 50.0, 24.0, 26.0, 30.0};
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

    solve1Tree(custos, lambda);


    return 0;
}
void solve1Tree(vector<vector<double>>& costs, vector<double>& lambda){
    vector<vector<double>> custos_linha(costs.size(), vector<double>(costs[0].size()));

    //- melhores distancias
    double menorCusto = INT_MAX;
    int best_j;
    int sec_best_j;


        for(int i = 0; i < costs.size(); i++){
            for(int j = i + 1; j < costs[0].size(); j++){
                custos_linha[i][j] = costs[i][j] - lambda[i] - lambda[j];
            }
        }
        for(int j = 1; j < costs[0].size(); j++){
            custos_linha[0][j] = costs[0][j] - lambda[0] - lambda[j];

            if(min(menorCusto, custos_linha[0][j]) == custos_linha[0][j]){
                sec_best_j = best_j;
                menorCusto = custos_linha[0][j];
                best_j = j;
            }   
        }

    // debug print
    /*
    for(int i = 0; i < costs.size(); i++){
        for(int j = 0; j < costs[0].size(); j++){
            cout << custos_linha[i][j] << ", ";
        }
        cout << endl;
    }
    cout << custos_linha[0][best_j] << ", " << custos_linha[0][sec_best_j] << endl;
    */

    Kruskal k(custos_linha);
    
}
