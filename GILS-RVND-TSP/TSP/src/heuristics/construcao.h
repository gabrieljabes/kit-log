#pragma once
#include <vector>
#include "../../../models/Data.h"
#include "../../../models/Solucao.h"

typedef struct{
    size_t noInserido;
    size_t arestaRemovida; // distancia {i, j} a ser removida para k entrar entre eles
    double custo;   
} InsertionInfo;

vector<InsertionInfo> calcularCustoInsercao(Solucao& s, vector<size_t>& CL, Data& tsp_info);
vector <size_t> Escolher3NosAleatorios(Data& tsp_info, vector <size_t>& CL); 
Solucao Construcao(Data& tsp_info);