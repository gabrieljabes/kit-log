#include "Data.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>

using namespace std;

typedef struct{
    vector <size_t> sequencia;
    double valorObj;
} Solucao;


typedef struct{
    size_t noInserido;
    size_t arestaRemovida; // distancia {i, j} a ser removida para k entrar entre eles
    double custo;   
} InsertionInfo;


vector<InsertionInfo> calcularCustoInsercao(Solucao& s, vector<size_t>& CL, Data& tsp_info);
void exibirSolucao(Solucao& s);
void calcularValorObj(Solucao& s, Data& dist);
vector <size_t> Escolher3NosAleatorios(Data& tsp_info, vector <size_t>& CL); 
vector<size_t> nosRestantes(Solucao& s, Data& tsp_info);
Solucao Construcao(Data& tsp_info);


int main(int argc, char** argv) {  
   
    srand(time(NULL));
    vector <size_t> CL;

    auto data = Data(argc, argv[1]);
    data.read();
    size_t n = data.getDimension(); 

    cout << "Dimension: " << n << endl;
    cout << "DistanceMatrix: " << endl;
    data.printMatrixDist(); 

    for(int i = 0; i < 5; i++){
    Solucao s = Construcao(data);
    calcularValorObj(s, data);
    exibirSolucao(s);
    }

    return 0;
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
    return s;
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

void exibirSolucao(Solucao& s){
    for(size_t i = 0; i < s.sequencia.size() - 1; i++) 
        cout << s.sequencia.at(i) << " -> ";
    cout << s.sequencia.back() << endl; 
    cout << "Custo: "<< s.valorObj << endl; 
}

void calcularValorObj(Solucao& s, Data& dist){
    s.valorObj = 0.0;
    for(size_t i = 0; i < s.sequencia.size() - 1; i++)
        s.valorObj+= dist.getDistance(s.sequencia[i], s.sequencia[i+1]);
}
