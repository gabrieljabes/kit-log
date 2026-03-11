#include "busca_local.h"
#include <algorithm>
using namespace std;

bool bestImprovementSwap(Solucao& s, Data& tsp_info){
    size_t best_i, best_j;
    double bestDelta{};
    for(size_t i = 1; i < s.sequencia.size() - 1; i++){
        size_t vi = s.sequencia[i];
        size_t vi_prev = s.sequencia [i - 1];
        size_t vi_next = s.sequencia [i + 1];
        for(size_t j = i + 1; j < s.sequencia.size() - 1; j++){
            size_t vj = s.sequencia[j];
            size_t vj_prev = s.sequencia[j - 1];
            size_t vj_next = s.sequencia[j + 1];

            double delta;

            if(j == i + 1){
                //caso em que vi e vj sao adjacentes
                delta = 
                - tsp_info.getDistance(vi_prev, vi)
                - tsp_info.getDistance(vj_next, vj)
                + tsp_info.getDistance(vi_prev, vj) 
                + tsp_info.getDistance(vj_next, vi);

            } else {
            delta = 
            //retira as arestas adjacentes de vi e vj (os que serao trocados caso valha a pena)
            - tsp_info.getDistance(vi_prev, vi)
            - tsp_info.getDistance(vi, vi_next)
            - tsp_info.getDistance(vj_prev, vj)
            - tsp_info.getDistance(vj, vj_next)
            // arestas novas caso ocorresse o swap
            + tsp_info.getDistance(vi_prev, vj)
            + tsp_info.getDistance(vi_next, vj)
            + tsp_info.getDistance(vj_prev, vi)
            + tsp_info.getDistance(vj_next, vi);
            }

            if(delta < bestDelta){
                bestDelta = delta;
                best_i = i;
                best_j = j;
            }
        }
    }
    

    if(bestDelta < 0){
        swap(s.sequencia[best_i], s.sequencia[best_j]);
        s.valorObj += bestDelta;
        return true;
    }
    return false;
}

bool bestImprovementOrOpt(Solucao& s, Data& tsp_info, int n){ 
    size_t best_i, best_j;
    double bestDelta{};
    for(size_t i = 1; i < s.sequencia.size() - 1 - n; i++){
        // definindo o primeiro e ultimo elemento do bloco
        size_t bloco_first = s.sequencia[i];
        size_t bloco_last  = s.sequencia[i + n - 1];
        
        size_t vi_prev = s.sequencia[i - 1];
        size_t vi_next = s.sequencia[i + n];

        for(size_t j = 0; j < s.sequencia.size() - 1; j++){
            // para garantir que j nao esteja contido no bloco
            if(j>= i - 1 &&  j <= i + n - 1) 
                continue;
            size_t vj = s.sequencia[j];
            size_t vj_prev = s.sequencia[j - 1];
            size_t vj_next = s.sequencia[j + 1];

            double delta =  
            - tsp_info.getDistance(vi_prev, bloco_first)
            - tsp_info.getDistance(bloco_last, vi_next)
            - tsp_info.getDistance(vj, vj_next)
            + tsp_info.getDistance(bloco_first, vj)
            + tsp_info.getDistance(bloco_last, vj_next)
            + tsp_info.getDistance(vi_prev, vi_next);

            if(delta < bestDelta){
                bestDelta = delta;
                best_i = i;
                best_j = j;
            }
        }
    }

    if(bestDelta < 0){
        vector <size_t> v;
        v.insert(v.begin(), s.sequencia.begin() + best_i, s.sequencia.begin() + best_i + n);

        if(best_i < best_j){
            s.sequencia.erase(s.sequencia.begin() + best_i, s.sequencia.begin() + best_i + n);
            s.sequencia.insert(s.sequencia.begin() - n + best_j + 1, v.begin(), v.end());
        }
            else{
                s.sequencia.erase(s.sequencia.begin() + best_i, s.sequencia.begin() + best_i + n);
                s.sequencia.insert(s.sequencia.begin() + best_j + 1, v.begin(), v.end());
            }
        s.valorObj += bestDelta;

        return true;
    }
    return false;
}

bool bestImprovement2Opt(Solucao& s, Data& tsp_info){
    size_t best_i, best_j;
    double bestDelta{};

    for(size_t i = 0; i < s.sequencia.size() - 3; i++){
        size_t vi = s.sequencia[i];
        size_t vi_prev = s.sequencia[i - 1];
        size_t vi_next = s.sequencia[i + 1];
        for(size_t j = i + 2; j < s.sequencia.size() - 1; j++){
            size_t vj = s.sequencia[j];
            size_t vj_prev = s.sequencia[j - 1];
            size_t vj_next = s.sequencia[j + 1];

            double delta =  
            - tsp_info.getDistance(vi, vi_next)
            - tsp_info.getDistance(vj, vj_next)
            + tsp_info.getDistance(vi, vj)
            + tsp_info.getDistance(vi_next, vj_next);

            if(delta < bestDelta){
                bestDelta = delta;
                best_i = i;
                best_j = j;
                
            }
        }
    }

    if(bestDelta < 0){
        reverse(s.sequencia.begin() + best_i + 1, s.sequencia.begin() + best_j + 1);
        s.valorObj += bestDelta;
        return true;
    }
    return false;
}

void BuscaLocal(Solucao& s, Data& tsp_info){
    vector <int> NL = {1, 2, 3, 4, 5};
    bool improved = false;

    while(NL.empty() == false)
    {
        int n = rand() % NL.size();
        switch(NL[n])
        {
        case 1:
            improved =  bestImprovementSwap(s, tsp_info);
            break;
        case 2:
            improved = bestImprovement2Opt(s, tsp_info);
            break;
        case 3:
            improved = bestImprovementOrOpt(s, tsp_info, 1);
            break;
        case 4:
            improved = bestImprovementOrOpt(s, tsp_info, 2);
            break;
        case 5:
            improved = bestImprovementOrOpt(s, tsp_info, 3);
            break;
        }
        if (improved)
            //admite todas as estruturas como opçoes novamente já que a soluçao mudou
            NL = {1, 2, 3, 4, 5};
        else
            //descarta a estrutura de vizinhança sorteada como opçao na proxima execuçao
            NL.erase(NL.begin() + n);
    }
}