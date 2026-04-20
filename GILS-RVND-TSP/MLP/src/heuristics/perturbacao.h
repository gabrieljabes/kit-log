#pragma once
#include "../../../models/Solucao.h"
#include "../../../models/Data.h"
#include "../../../models/aux_structures.h"

Solucao Perturbacao(Solucao& s, Data& problem_info, vector<vector<Subsequence>>& matrix);