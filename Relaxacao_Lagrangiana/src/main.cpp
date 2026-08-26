#include <bits/stdc++.h>
#include "Kruskal.h"
#include "OneTree.h"
#include "Data.h"
#include "node.h"

using namespace std;

int main(int argc, char** argv) {  
   
    srand(time(NULL));
    
    auto data = Data(argc, argv[1]);
    data.read();
    size_t n = data.getDimension(); 

    cout << "Dimension: " << n << endl;
    cout << "DistanceMatrix: " << endl;
    data.printMatrixDist(); 

    double ub = 148.0;
    vector<double> lambda_inicial(n, 0);
    vector<vector<double>> custo(n, vector<double>(n));
    
        for(int i = 0; i < n; i++){
            for(int j = i + 1; j < n; j++){
                custo[i][j] = data.getDistance(i + 1, j + 1) - lambda_inicial[i] - lambda_inicial[j];
                custo[j][i] = custo[i][j];
            }
        }

    Node node;
    node.lambda = lambda_inicial;
    updateNode(node, ub, custo);
    cout << "lb =" << node.tree.LB << " choosen =" << node.choosen<< " tour =" << node.tree.is_tour << endl;

    return 0;
}   
