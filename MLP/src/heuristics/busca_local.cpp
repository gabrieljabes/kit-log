#include "busca_local.h"
#include <algorithm>
using namespace std;

bool bestImprovementSwap(Solucao& s, Data& problem_info, vector <vector<Subsequence>>& matrix){

   size_t n = matrix.size();
   double best_delta = 0;
   size_t best_i = -1;
   size_t best_j = -1;

    for(size_t i = 1; i < matrix.size() - 1; i++){
        size_t i_prev = i - 1;
        size_t i_next = i + 1;

        for(size_t j = i + 1; j < matrix.size() - 1; j++){
            size_t j_prev = j - 1;
            size_t j_next = j + 1;

            Subsequence *particoes[5];

            particoes[0] = &matrix[0][i_prev];
            particoes[1] = &matrix[j][j];
            particoes[2] = &matrix[i_next][j_prev]; 
            particoes[3] = &matrix[i][i];
            particoes[4] = &matrix[j_next][n - 1];

            Subsequence reconstrucao = *particoes[0];

            for(int k = 1; k < 5; k++){
                if(k == 2 && i == j_prev)
                    continue;
                reconstrucao = Subsequence::Concatenate(reconstrucao,*particoes[k], problem_info);
            }

            double delta = reconstrucao.C - matrix[0][n - 1].C;

            if(delta < best_delta){
                best_delta = delta;
                best_i = i;
                best_j = j;
            }
        }
    }

     if(best_delta < 0){
        swap(s.sequencia[best_i], s.sequencia[best_j]);
        s.valorObj += best_delta;
        return true;
    }
    return false;
}
