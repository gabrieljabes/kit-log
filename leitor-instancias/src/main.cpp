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


vector<InsertionInfo> calcularCustoInsercao(Solucao& s, vector<size_t>& CL, Data& dist);
void exibirSolucao(Solucao& s);
void calcularValorObj(Solucao& s, Data& dist);
vector <size_t> Escolher3NosAleatorios(Solucao& s, Data tsp_info, vector <size_t>& CL); 
vector<size_t> nosRestantes(Solucao& s, Data tsp_info);



int main(int argc, char** argv) {   
   
    Solucao s;
    s.sequencia = {1, 1};

    vector <size_t> CL;

    auto data = Data(argc, argv[1]);
    data.read();
    size_t n = data.getDimension(); 

    cout << "Dimension: " << n << endl;
    cout << "DistanceMatrix: " << endl;
    data.printMatrixDist(); 


    s.sequencia = Escolher3NosAleatorios(s, data, CL);

    calcularValorObj(s, data);

    exibirSolucao(s);


    //exibir lista de candidatos
    for (auto& i : CL)
    cout << i << " ";
    cout << endl;

    // for(size_t i = 0; i < n; i++){
    //     s.sequencia.push_back(i + 1);
    // }

    // calcularValorObj(&s, &data);

    // exibirSolucao(&s);


    
    return 0;
}

vector <size_t> Escolher3NosAleatorios(Solucao& s, Data tsp_info, vector <size_t>& CL){
    unsigned seed = chrono::system_clock::now().time_since_epoch().count(); // seed para randomizaçao baseado no tempo do sistema
    int n = tsp_info.getDimension();
    vector<size_t> vertices (n-1); // -1 para não levar em conta o 1
    vector<size_t> ss = s.sequencia;

    for(int i = 0; i < n-1; i++)
        vertices[i] = i+2;
    
    shuffle(vertices.begin(), vertices.end(), default_random_engine(seed)); // embaralha vetor com todos os vértices

    ss.insert (ss.begin()+1, vertices.begin(), vertices.begin()+3); // insere os três primeiros na sequencia

    CL = vertices;
    CL.erase(CL.begin(), CL.begin()+3); // guarda os nós restantes na lista de candidatos
    
    return ss;
}

vector<InsertionInfo> calcularCustoInsercao(Solucao& s, vector<size_t>& CL, Data& dist){
    // o tamanho do vetor  tem que ter o tamanho da quantidade de possibilidades possiveis, isto é, a quantidade de inserçoes possiveis * qnt de candidatos
    vector<InsertionInfo> custoInsercao = vector<InsertionInfo>((s.sequencia.size() - 1 ) * CL.size());  

    int l{};
    for(int a = 0; a < s.sequencia.size() - 1; a++){
        //toda vez q esse for loopar, os indices serao atualizados para os vértices da sequência
        int i = s.sequencia.at(a);
        int j = s.sequencia.at(a+1);
        for(size_t k : CL) {
            // aqui testa todos os candidatos para saber o custo de inserção
            custoInsercao[l].custo = dist.getDistance(s.sequencia[i], s.sequencia[k]) + dist.getDistance(s.sequencia[k], s.sequencia[j]) - dist.getDistance(s.sequencia[i], s.sequencia[j]);
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
