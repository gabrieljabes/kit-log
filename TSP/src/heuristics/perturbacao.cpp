#include "perturbacao.h"
#include <vector>
#include <random>
using namespace std;

Solucao Perturbacao(Solucao& s, Data& tsp_info){
    Solucao s_linha = s;
    
    //tamanho maximo de um bloco
    size_t max_tamanho = max((size_t)2, (size_t)ceil(tsp_info.getDimension()/10.0));
    //tamanho maximo entre os gaps


    //tamanho dos blocos
    size_t A = rand() % (max_tamanho - 1) + 2;
    size_t B = rand() % (max_tamanho - 1) + 2;

     //espaço dos gaps
     size_t total_gaps = tsp_info.getDimension() - A - B - 1;
     size_t gap1 = rand() % (total_gaps - 1);
     total_gaps -= gap1;
     size_t gap2 = rand() % (total_gaps - 1) + 1;

    //posiçoes
    auto p_A = gap1 + 1;
    auto p_B = p_A + A + gap2;

    //blocos
    vector <size_t> bloco_a; 
    vector <size_t> bloco_b;

    //movimentos pra trocar os blocos de posiçao
    bloco_a.insert(bloco_a.begin(), s.sequencia.begin() + p_A, s.sequencia.begin() + p_A + A);
    bloco_b.insert(bloco_b.begin(), s.sequencia.begin() + p_B, s.sequencia.begin() + p_B + B);

    s_linha.sequencia.erase(s_linha.sequencia.begin() + p_B, s_linha.sequencia.begin() + p_B + B);
    s_linha.sequencia.erase(s_linha.sequencia.begin() + p_A, s_linha.sequencia.begin() + p_A + A);


    s_linha.sequencia.insert(s_linha.sequencia.begin() + p_A, bloco_b.begin(), bloco_b.end());
    s_linha.sequencia.insert(s_linha.sequencia.begin() + (p_B - A + B), bloco_a.begin(), bloco_a.end());

    calcularValorObj(s_linha, tsp_info);
    return s_linha;
}