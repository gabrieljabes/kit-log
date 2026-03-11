#include "ILS.h"
#include "construcao.h"
#include "busca_local.h"
#include "perturbacao.h"
using namespace std;

Solucao ILS(int& maxIter, int& maxIterILS, Data& tsp_info){
    Solucao bestOfAll;
    bestOfAll.valorObj = INFINITY;
    for(int i = 0; i < maxIter; i++){
        Solucao s = Construcao(tsp_info);
        Solucao best = s;

        int iterIls = 0;

        while(iterIls <= maxIterILS){
            BuscaLocal(s, tsp_info);
            if(s.valorObj < best.valorObj){
                best = s;
                iterIls = 0;
            }
            s = Perturbacao(best, tsp_info);
            iterIls++;
        }
        if(best.valorObj < bestOfAll.valorObj)
            bestOfAll = best;
    }

    return bestOfAll;
}