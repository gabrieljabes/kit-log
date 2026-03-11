#include <iostream>
#include <chrono>

#include "models/Data.h"
#include "models/Solucao.h"
#include "heuristics/ILS.h"


int main(int argc, char** argv) {  
   

    srand(time(NULL));
    
    vector <size_t> CL;
    bool improved = false;

    auto data = Data(argc, argv[1]);
    data.read();
    size_t n = data.getDimension(); 

    cout << "Dimension: " << n << endl;
    cout << "DistanceMatrix: " << endl;
    data.printMatrixDist(); 

    int maxIter = 50;
    int maxIterILS = (data.getDimension() >= 150) ? ceil(data.getDimension()/2) : data.getDimension();
    cout << maxIterILS << endl;

    auto t1 = chrono::high_resolution_clock::now();

    Solucao s = ILS(maxIter, maxIterILS, data);

    auto t2 = chrono::high_resolution_clock::now();

    exibirSolucao(s);

    double tempo = chrono::duration<double>(t2 - t1).count();
    cout << "tempo de execução: " << tempo << endl;

    return 0;
}

