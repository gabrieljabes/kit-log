#include "construcao.h"
#include <algorithm>
#include <random>
using namespace std;

vector<InsertionInfo> calcularCustoInsercao(Solucao& s, vector<size_t>& CL, Data& tsp_info){
    // o tamanho do vetor  tem que ter o tamanho da quantidade de possibilidades possiveis, isto é, a quantidade de inserçoes possiveis * qnt de candidatos
    vector<InsertionInfo> custoInsercao = vector<InsertionInfo>((s.sequencia.size() - 1 ) * CL.size());  

    int l{};
    for(int a = 0; a < s.sequencia.size() - 1; a++){
        //toda vez q esse for loopar, os indices serao atualizados para os vértices da sequência
        int i = s.sequencia.at(a);
        int j = s.sequencia.at(a+1);
        for(size_t k : CL) {
            // aqui testa todos os candidatos para saber o custo de inserção' 
            custoInsercao[l].custo = tsp_info.getDistance(i, k) + tsp_info.getDistance(k, j) - tsp_info.getDistance(i, j);
            custoInsercao[l].noInserido = k;
            custoInsercao[l].arestaRemovida = a;
            l++;
        }
    }
    return custoInsercao;
}


vector <size_t> Escolher3NosAleatorios(Data& tsp_info, vector <size_t>& CL){
    Solucao s;
    s.sequencia = {1, 1};

    int n = tsp_info.getDimension();
    vector<size_t> vertices (n-1); // -1 para não levar em conta o 1

    for(int i = 0; i < n-1; i++)
        vertices[i] = i+2;

    for(int i = 0; i < 3; i++){
        int l = rand() % vertices.size(); // indice aleatorio 
        size_t noEscolhido = vertices[l];
        
        s.sequencia.insert(s.sequencia.begin() + 1, noEscolhido);

        // remove o noEscolhido dos vertices para n sortear dnv
        vertices.erase(vertices.begin() + l);
    }

    CL = vertices;

    return s.sequencia;
}


Solucao Construcao(Data& tsp_info){
    Solucao s;
    vector<size_t> CL;
    s.sequencia = Escolher3NosAleatorios(tsp_info, CL);

    while(!CL.empty()) {
        vector <InsertionInfo> custoInsercao = calcularCustoInsercao(s, CL, tsp_info);
        sort(custoInsercao.begin(), custoInsercao.end(), [](const InsertionInfo &a, const InsertionInfo &b) {return a.custo < b.custo;});
        double alpha = (double) rand() / RAND_MAX;
        int selecionado = rand() % ((int) ceil(alpha * custoInsercao.size()));
        s.sequencia.insert(s.sequencia.begin() + custoInsercao[selecionado].arestaRemovida + 1, custoInsercao[selecionado].noInserido);
        CL.erase(remove(CL.begin(), CL.end(), custoInsercao[selecionado].noInserido), CL.end()); // tira o "noInserido" do CL
    }
    calcularValorObj(s, tsp_info);
    return s;
}