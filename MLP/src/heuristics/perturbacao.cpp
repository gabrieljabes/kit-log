#include "busca_local.h"
#include "perturbacao.h"
#include <algorithm>

Solucao Perturbacao(Solucao& s, Data& problem_info, vector<vector<Subsequence>>& matrix){
    Solucao s_linha = s;
    
    size_t max = (size_t)ceil(problem_info.getDimension()/10.0);

    size_t A = rand() % (max - 1) + 2;
    size_t B = rand() % (max - 1) + 2;

     size_t total_gaps = problem_info.getDimension() - A - B - 1;
     size_t gap1 = rand() % (total_gaps - 1);
     total_gaps -= gap1;
     size_t gap2 = rand() % (total_gaps - 1) + 1;

    auto p_A = gap1 + 1;
    auto p_B = p_A + A + gap2;

    vector <size_t> bloco_a; 
    vector <size_t> bloco_b;

    bloco_a.insert(bloco_a.begin(), s.sequencia.begin() + p_A, s.sequencia.begin() + p_A + A);
    bloco_b.insert(bloco_b.begin(), s.sequencia.begin() + p_B, s.sequencia.begin() + p_B + B);

    s_linha.sequencia.erase(s_linha.sequencia.begin() + p_B, s_linha.sequencia.begin() + p_B + B);
    s_linha.sequencia.erase(s_linha.sequencia.begin() + p_A, s_linha.sequencia.begin() + p_A + A);


    s_linha.sequencia.insert(s_linha.sequencia.begin() + p_A, bloco_b.begin(), bloco_b.end());
    s_linha.sequencia.insert(s_linha.sequencia.begin() + (p_B - A + B), bloco_a.begin(), bloco_a.end());

    UpdateAllSubseq(s, matrix, problem_info);
    s.valorObj = matrix[0][s.sequencia.size()-1].C;

    return s_linha;
}