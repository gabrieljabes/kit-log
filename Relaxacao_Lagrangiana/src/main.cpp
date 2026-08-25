#include <bits/stdc++.h>
#include "Kruskal.h"
#include "OneTree.h"
#include "Data.h"

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
    
    OneTree t = SubgradientMethod(ub, data);

    return 0;
}   
