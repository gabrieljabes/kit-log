#pragma once
#include "Data.h"
#include "Solucao.h"


struct Subsequence{
    double T; // tempo do bloco
    double C; // latencia do bloco
    int W; // custo de atraso ou qnt de elementos na subsequencia;
    int first, last;

    inline static Subsequence Concatenate(Subsequence& sigma1, Subsequence& sigma2, Data& tmp){
        Subsequence sigma;
        // tempo da ponte entre o sigma1.last e sigma2.first
        double temp = tmp.getDistance(sigma1.last, sigma2.first);
        sigma.W = sigma1.W + sigma2.W;
        sigma.T = sigma1.T + temp + sigma2.T;
        sigma.C = sigma1.C + sigma2.W * (sigma1.T + temp) + sigma2.C;
        sigma.first = sigma1.first;
        sigma.last = sigma2.last;

        return sigma;
    }

};

    inline void UpdateAllSubseq(Solucao& s, vector<vector<Subsequence>>& subseq_matrix, Data& problem_info){
        int n = s.sequencia.size();

        //subsequencias de um unico nó de acordo com a pag 29
        for(int i = 0; i < n; i++){
            subseq_matrix[i][i].W = (i > 0);
            subseq_matrix[i][i].C = 0;
            subseq_matrix[i][i].T = 0;
            subseq_matrix[i][i].first = s.sequencia[i];
            subseq_matrix[i][i].last = s.sequencia[i];
        }

        for(int i = 0; i < n; i++)
            for(int j = i + 1; j < n; j++)
                subseq_matrix[i][j] = Subsequence::Concatenate(subseq_matrix[i][j-1], subseq_matrix[j][j], problem_info);

        for(int i = n - 1; i >= 0; i--)
            for(int j = i - 1; j >= 0; j--)
                subseq_matrix[i][j] = Subsequence::Concatenate(subseq_matrix[i][j+1], subseq_matrix[j][j], problem_info);
    }
    