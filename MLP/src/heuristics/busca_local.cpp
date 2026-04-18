#include "busca_local.h"
#include <algorithm>
using namespace std;

bool bestImprovementSwap(Solucao& s, Data& problem_info, vector <vector<Subsequence>>& matrix){
   size_t n = matrix.size();
   double best_delta = 0;
   size_t best_i, best_j;

    for(size_t i = 1; i < matrix.size() - 1; i++){

        for(size_t j = i + 1; j < matrix.size() - 1; j++){

            Subsequence *particoes[5];

            particoes[0] = &matrix[0][i - 1];
            particoes[1] = &matrix[j][j];
            particoes[2] = &matrix[i + 1][j - 1]; 
            particoes[3] = &matrix[i][i];
            particoes[4] = &matrix[j + 1][n - 1];

            Subsequence reconstrucao = *particoes[0];

            for(int k = 1; k < 5; k++){
                if(k == 2 && i == j - 1)
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

bool bestImprovementOrOpt(Solucao& s, Data& problem_info, vector <vector<Subsequence>>& matrix, int m){
    size_t n = matrix.size();
    size_t best_i, best_j;
    double best_delta = 0;

    for(size_t i = 1; i < matrix.size() - 1 - m; i++){
        for(size_t j = 0; j < matrix.size() - 1; j++){
            if(j >= i - 1 &&  j <= i + m - 1) 
                continue;

            Subsequence *particoes[5];
            if(i < j){
                particoes[0] = &matrix[0][i - 1];
                particoes[1] = &matrix[i + m][j - 1];
                particoes[2] = &matrix[j][j]; 
                particoes[3] = &matrix[i][i + m - 1];
                particoes[4] = &matrix[j + 1][n - 1];
            } else if(i > j){
                particoes[0] = &matrix[0][j - 1];
                particoes[1] = &matrix[j][j];
                particoes[2] = &matrix[i][i + m - 1]; 
                particoes[3] = &matrix[j + 1][i - 1];
                particoes[4] = &matrix[i + m][n - 1];
            }

            Subsequence reconstrucao;
            int start_k = 1;
            if(j == 0){
                reconstrucao = *particoes[1];
                start_k = 2;
            }else{
                reconstrucao = *particoes[0];
                start_k = 1;
            }

            for(int k = start_k; k < 5; k++){
                if(i < j && k == 1 && i + m == j)
                    continue;

                reconstrucao = Subsequence::Concatenate(reconstrucao,*particoes[k], problem_info);
            }

            double delta = reconstrucao.C - matrix[0][n-1].C;

            if(delta < best_delta){
                best_delta = delta;
                best_i = i;
                best_j = j;
            }
        }
    }

   if(best_delta < 0){
        vector <size_t> v;
        v.insert(v.begin(), s.sequencia.begin() + best_i, s.sequencia.begin() + best_i + m);

        if(best_i < best_j){
            s.sequencia.erase(s.sequencia.begin() + best_i, s.sequencia.begin() + best_i + m);
            s.sequencia.insert(s.sequencia.begin() - m + best_j + 1, v.begin(), v.end());
        }
            else{
                s.sequencia.erase(s.sequencia.begin() + best_i, s.sequencia.begin() + best_i + m);
                s.sequencia.insert(s.sequencia.begin() + best_j + 1, v.begin(), v.end());
            }
        s.valorObj += best_delta;

        return true;
    }
    return false;
}


bool bestImprovement2Opt(Solucao& s, Data& problem_info, vector <vector<Subsequence>>& matrix){
    size_t n = matrix.size();
    size_t best_i, best_j;
    double best_delta = 0;

    for(size_t i = 1; i < matrix.size() - 2; i++){
        for(size_t j = i+1; j < matrix.size() - 1; j++){

                Subsequence *particoes[3];

                particoes[0] = &matrix[0][i - 1];
                particoes[1] = &matrix[j][i];
                particoes[2] = &matrix[j + 1][n - 1];
                
                Subsequence reconstrucao = *particoes[0];
                for(int k = 1; k < 3; k++)
                    reconstrucao = Subsequence::Concatenate(reconstrucao, *particoes[k], problem_info);

                double delta = reconstrucao.C - matrix[0][n - 1].C;
                
            if(delta < best_delta){
                best_delta = delta;
                best_i = i;
                best_j = j;
            }
        }
    }

    if(best_delta < 0){
        reverse(s.sequencia.begin() + best_i, s.sequencia.begin() + best_j + 1);
        s.valorObj += best_delta;
        return true;

    }
    return false;
}