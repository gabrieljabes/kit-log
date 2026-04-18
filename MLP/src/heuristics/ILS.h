#pragma once
#include "../models/Solucao.h"
#include "../models/aux_structures.h"
#include "busca_local.h"
#include "perturbacao.h"
#include "../models/Data.h"

Solucao ILS(int& maxIter, int& maxIterILS, Data& problem_info, vector <vector<Subsequence>>& matrix);