#include "Data.h"
#include <iostream>
#include <vector>
#include <algorithm>

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

vector<InsertionInfo> calcularCustoInsercao(Solucao& s, vector<size_t>& CL, Data& dist){
    vector<InsertionInfo> custoInsercao = vector<InsertionInfo>((s.sequencia.size() - 1 ) * CL.size()); 

    int l{};
    for(int a = 0; a < s.sequencia.size() - 1; a++){
        int i = s.sequencia.at(a);
        int j = s.sequencia.at(a+1);
        for(size_t k : CL) {
            custoInsercao[l].custo = dist.getDistance(s.sequencia[i], s.sequencia[k]) + dist.getDistance(s.sequencia[k], s.sequencia[j]) - dist.getDistance(s.sequencia[i], s.sequencia[j]);
            custoInsercao[l].noInserido = k;
            custoInsercao[l].arestaRemovida = a;
            l++;
        }
    }
    return custoInsercao;
}

void exibirSolucao(Solucao *s){
    {
    for(int i = 0; i < s->sequencia.size() - 1; i++) // -1 pois a exibição final será fora do for;
        cout << s->sequencia.at(i) << " -> ";
    cout << s->sequencia.back() << " -> " << s->sequencia.at(0) << endl; //exibe ultimo elemento da sequencia e o primeiro
    cout << "Custo: "<< s->valorObj << endl; // exibe custo
    }
}

void calcularValorObj(Solucao *s, Data *dist){
    s->valorObj = 0.0;
    for(size_t i = 0; i < s->sequencia.size() - 1; i++)
        s->valorObj+= dist->getDistance(s->sequencia[i], s->sequencia[i+1]);
    s->valorObj+= dist->getDistance(s->sequencia.at(0), s->sequencia.back()); //distancia do primeiro e ultimo vertice
}

int main(int argc, char** argv) {   
   
    Solucao s;

    auto data = Data(argc, argv[1]);
    data.read();
    size_t n = data.getDimension(); // size_t = unsigned long long / tamanho da dimensao

    cout << "Dimension: " << n << endl;
    cout << "DistanceMatrix: " << endl;
    data.printMatrixDist(); //exibe as distancias da matriz


    //testando soluçao com sequencia de 1 a 29 sequencialmente
    for(size_t i = 0; i < n; i++){
        s.sequencia.push_back(i + 1);
    }

    calcularValorObj(&s, &data);

    exibirSolucao(&s);

    // cout << "Exemplo de Solucao s = ";
    // double cost = 0.0;
    // for (size_t i = 1; i < n; i++) {
    //     cout << i << " -> ";
    //     cost += data.getDistance(i, i+1); // calcula o custo da rota
    // }
    // cost += data.getDistance(n, 1);
    // cout << n << " -> " << 1 << endl;
    // cout << "Custo de S: " << cost << endl;

    return 0;
}
