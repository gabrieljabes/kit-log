#include <bits/stdc++.h>

#include "models/Data.h"
#include "models/Solucao.h"
#include "models/aux_structures.h"
#include "heuristics/busca_local.h"
#include "heuristics/construcao.h"
#include "heuristics/perturbacao.h"
#include "heuristics/ILS.h"

bool bestImprovementSwap(Solucao& s, Data& problem_info, vector <vector<Subsequence>>& matrix);
Solucao Construcao(Data& problem_info);
vector<size_t> ListaCandidatos(Data& problem_info);

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

    vector<vector<Subsequence>> subseq_matrix (n+1, vector<Subsequence>(n+1));

    auto t1 = chrono::high_resolution_clock::now();
    Solucao s = ILS(maxIter, maxIterILS, data, subseq_matrix);
    auto t2 = chrono::high_resolution_clock::now();

    double tempo = chrono::duration<double>(t2 - t1).count();

    cout << fixed << setprecision(0);
    exibirSolucao(s);
    cout << defaultfloat << setprecision(6);
    cout << "tempo de execução: " << tempo << endl;

    return 0;
}

