#include "ILS.h"
#include "construcao.h"
#include "busca_local.h"
#include "perturbacao.h"
using namespace std;

Solucao ILS(int& maxIter, int& maxIterILS, Data& problem_info, vector <vector<Subsequence>>& matrix){
    Solucao bestOfAll;
    bestOfAll.valorObj = INFINITY;
    for(int i = 0; i < maxIter; i++){
        Solucao s = Construcao(problem_info);
            UpdateAllSubseq(s, matrix, problem_info);
            s.valorObj = matrix[0][s.sequencia.size()-1].C;
        Solucao best = s;

        int iterIls = 0;

        while(iterIls <= maxIterILS){
            BuscaLocal(s, problem_info, matrix);
            if(s.valorObj < best.valorObj){
                best = s;
                iterIls = 0;
            }
            s = Perturbacao(best, problem_info, matrix);
            iterIls++;
        }
        if(best.valorObj < bestOfAll.valorObj)
            bestOfAll = best;
    }

    return bestOfAll;
}