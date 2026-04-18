#pragma once

#include "../models/Data.h"
#include "../models/Solucao.h"
#include "../models/aux_structures.h"

bool bestImprovementSwap(Solucao& s, Data& problem_info, vector <vector<Subsequence>>& matrix);
bool bestImprovement2Opt(Solucao& s, Data& problem_info, vector <vector<Subsequence>>& matrix);
bool bestImprovementOrOpt(Solucao& s, Data& problem_info, vector <vector<Subsequence>>& matrix, int n);

void BuscaLocal(Solucao& s, Data& problem_info);

