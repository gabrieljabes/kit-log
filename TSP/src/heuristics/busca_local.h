#pragma once

#include "../models/Data.h"
#include "../models/Solucao.h"

bool bestImprovementSwap(Solucao& s, Data& tsp_info);
bool bestImprovement2Opt(Solucao& s, Data& tsp_info);
bool bestImprovementOrOpt(Solucao& s, Data& tsp_info, int n);

void BuscaLocal(Solucao& s, Data& tsp_info);

