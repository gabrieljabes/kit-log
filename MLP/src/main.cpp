#include <iostream>
#include <chrono>

#include "models/Data.h"
#include "models/Solucao.h"
#include "models/aux_structures.h"
#include "heuristics/ILS.h"


int main(int argc, char** argv) {  
    auto data = Data(argc, argv[1]);
    data.read();
    size_t n = data.getDimension(); 

    cout << "Dimension: " << n << endl;
    cout << "DistanceMatrix: " << endl;
    data.printMatrixDist(); 

    int maxIter = 50;
    int maxIterILS = (data.getDimension() >= 150) ? ceil(data.getDimension()/2) : data.getDimension();
    cout << maxIterILS << endl;

    return 0;
}

void UpdateAllSubseq(Solucao& s, vector<vector<Subsequence>>& subseq_matrix, Data& problem_info){
    int n = s.sequencia.size();

    //subsequencias de um unico nó de acordo com a pag 29
    for(int i = 0; i < n; i++){
        //caso em [0][0] = 0
        subseq_matrix[i][i].T = (i > 0);
        subseq_matrix[i][i].C = 0;
        subseq_matrix[i][i].W = 1;
    }

    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j ++)
            subseq_matrix[i][j] = Subsequence::Concatenate(subseq_matrix[i][j-1], subseq_matrix[i][j], problem_info);

}

