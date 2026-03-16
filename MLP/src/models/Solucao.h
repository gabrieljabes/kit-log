#pragma once

#include <vector>
#include <iostream>
#include "Data.h"
using namespace std;

typedef struct{
    vector <size_t> sequencia;
    double valorObj;
} Solucao;

inline void exibirSolucao(Solucao& s){
    for(size_t i = 0; i < s.sequencia.size() - 1; i++) 
        cout << s.sequencia.at(i) << " -> ";
    cout << s.sequencia.back() << endl; 
    cout << "Custo: "<< s.valorObj << endl; 
}

inline void calcularValorObj(Solucao& s, Data& dist){
    s.valorObj = 0.0;
    for(size_t i = 0; i < s.sequencia.size() - 1; i++)
        s.valorObj+= dist.getDistance(s.sequencia[i], s.sequencia[i+1]);
}