#pragma once
#include "Data.h"


typedef struct{
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


} Subsequence;