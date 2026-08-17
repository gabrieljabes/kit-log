#include <bits/stdc++.h>
#include "Data.h"
#include "OneTree.h"

using namespace std;

OneTree SubgradientMethod(double& ub, vector<vector<double>>& costs){
    int dim = costs.size();
    double epsilon_min = pow(10, -5);
    int k_max = 30;
    
    int k = 0;
    double epsilon = 1;
    vector<double> lambda(dim, 0);
    


    //while(epsilon > epsilon_min) && 
}