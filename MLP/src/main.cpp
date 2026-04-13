#include <bits/stdc++.h>

#include "models/Data.h"
#include "models/Solucao.h"
#include "models/aux_structures.h"

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

    int maxIter = 50;
    int maxIterILS = (data.getDimension() >= 150) ? ceil(data.getDimension()/2) : data.getDimension();
    cout << maxIterILS << endl;
    Solucao s = Construcao(data);

    vector<vector<Subsequence>> subseq_matrix (n+1, vector<Subsequence>(n+1));
    UpdateAllSubseq(s, subseq_matrix, data);

    s.valorObj = subseq_matrix[0][s.sequencia.size()-1].C;
    exibirSolucao(s);


    return 0;
}

