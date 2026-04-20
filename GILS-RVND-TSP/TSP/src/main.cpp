#include <iostream>
#include <chrono>

#include "../../models/Data.h"
#include "../../models/Solucao.h"
#include "heuristics/ILS.h"


int main(int argc, char** argv) {  
   

    srand(time(NULL));
    
    auto data = Data(argc, argv[1]);
    data.read();
    size_t n = data.getDimension(); 

    cout << "Dimension: " << n << endl;
    cout << "DistanceMatrix: " << endl;
    data.printMatrixDist(); 

    int maxIter = 10;
    int maxIterILS = min((size_t)100, n);
    cout << maxIterILS << endl;

    auto t1 = chrono::high_resolution_clock::now();

    Solucao s = ILS(maxIter, maxIterILS, data);

    auto t2 = chrono::high_resolution_clock::now();

    exibirSolucao(s);

    double tempo = chrono::duration<double>(t2 - t1).count();
    cout << "tempo de execução: " << tempo << endl;

    return 0;
}

