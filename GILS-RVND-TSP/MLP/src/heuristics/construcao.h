#pragma once
#include <vector>
#include <algorithm>
#include "../../../models/Data.h"
#include "../../../models/Solucao.h"
#include "../../../models/aux_structures.h"

Solucao Construcao(Data& problem_info);
vector<size_t> ListaCandidatos(Data& problem_info);
