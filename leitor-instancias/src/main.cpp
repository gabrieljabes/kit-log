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
bool bestImprovementSwap(Solucao& s, Data& tsp_info);
bool bestImprovement2Opt(Solucao& s, Data& tsp_info);
bool bestImprovementOrOpt(Solucao& s, Data& tsp_info, int n);
void BuscaLocal(Solucao& s, Data& tsp_info);
Solucao Perturbacao(Solucao& s, Data& tsp_info);
Solucao ILS(int& maxIter, int& maxIterILS, Data& tsp_info);



int main(int argc, char** argv) {  
   
    srand(time(NULL));
    
    vector <size_t> CL;
    bool improved = false;

    auto data = Data(argc, argv[1]);
    data.read();
    size_t n = data.getDimension(); 

    cout << "Dimension: " << n << endl;
    cout << "DistanceMatrix: " << endl;
    data.printMatrixDist(); 

    int maxIter = 50;
    int maxIterILS = (data.getDimension() >= 150) ? ceil(data.getDimension()/2) : data.getDimension();
    cout << maxIterILS << endl;

    Solucao s = ILS(maxIter, maxIterILS, data);
    exibirSolucao(s);

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
    calcularValorObj(s, tsp_info);
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

bool bestImprovementSwap(Solucao& s, Data& tsp_info){
    size_t best_i, best_j;
    double bestDelta{};
    for(size_t i = 1; i < s.sequencia.size() - 1; i++){
        size_t vi = s.sequencia[i];
        size_t vi_prev = s.sequencia [i - 1];
        size_t vi_next = s.sequencia [i + 1];
        for(size_t j = i + 1; j < s.sequencia.size() - 1; j++){
            size_t vj = s.sequencia[j];
            size_t vj_prev = s.sequencia[j - 1];
            size_t vj_next = s.sequencia[j + 1];

            double delta;

            if(j == i + 1){
                //caso em que vi e vj sao adjacentes
                delta = 
                - tsp_info.getDistance(vi_prev, vi)
                - tsp_info.getDistance(vj_next, vj)
                + tsp_info.getDistance(vi_prev, vj) 
                + tsp_info.getDistance(vj_next, vi);

            } else {
            delta = 
            //retira as arestas adjacentes de vi e vj (os que serao trocados caso valha a pena)
            - tsp_info.getDistance(vi_prev, vi)
            - tsp_info.getDistance(vi, vi_next)
            - tsp_info.getDistance(vj_prev, vj)
            - tsp_info.getDistance(vj, vj_next)
            // arestas novas caso ocorresse o swap
            + tsp_info.getDistance(vi_prev, vj)
            + tsp_info.getDistance(vi_next, vj)
            + tsp_info.getDistance(vj_prev, vi)
            + tsp_info.getDistance(vj_next, vi);
            }

            if(delta < bestDelta){
                bestDelta = delta;
                best_i = i;
                best_j = j;
            }
        }
    }
    

    if(bestDelta < 0){
        swap(s.sequencia[best_i], s.sequencia[best_j]);
        s.valorObj += bestDelta;
        return true;
    }
    return false;
}

bool bestImprovementOrOpt(Solucao& s, Data& tsp_info, int n){ 
    size_t best_i, best_j;
    double bestDelta{};
    for(size_t i = 1; i < s.sequencia.size() - 1 - n; i++){
        // definindo o primeiro e ultimo elemento do bloco
        size_t bloco_first = s.sequencia[i];
        size_t bloco_last  = s.sequencia[i + n - 1];
        
        size_t vi_prev = s.sequencia[i - 1];
        size_t vi_next = s.sequencia[i + n];

        for(size_t j = 0; j < s.sequencia.size() - 1; j++){
            // para garantir que j nao esteja contido no bloco
            if(j>= i - 1 &&  j <= i + n - 1) 
                continue;
            size_t vj = s.sequencia[j];
            size_t vj_prev = s.sequencia[j - 1];
            size_t vj_next = s.sequencia[j + 1];

            double delta =  
            - tsp_info.getDistance(vi_prev, bloco_first)
            - tsp_info.getDistance(bloco_last, vi_next)
            - tsp_info.getDistance(vj, vj_next)
            + tsp_info.getDistance(bloco_first, vj)
            + tsp_info.getDistance(bloco_last, vj_next)
            + tsp_info.getDistance(vi_prev, vi_next);

            if(delta < bestDelta){
                bestDelta = delta;
                best_i = i;
                best_j = j;
            }
        }
    }

    if(bestDelta < 0){
        vector <size_t> v;
        v.insert(v.begin(), s.sequencia.begin() + best_i, s.sequencia.begin() + best_i + n);

        if(best_i < best_j){
            s.sequencia.erase(s.sequencia.begin() + best_i, s.sequencia.begin() + best_i + n);
            s.sequencia.insert(s.sequencia.begin() - n + best_j + 1, v.begin(), v.end());
        }
            else{
                s.sequencia.erase(s.sequencia.begin() + best_i, s.sequencia.begin() + best_i + n);
                s.sequencia.insert(s.sequencia.begin() + best_j + 1, v.begin(), v.end());
            }
        s.valorObj += bestDelta;

        return true;
    }
    return false;
}

bool bestImprovement2Opt(Solucao& s, Data& tsp_info){
    size_t best_i, best_j;
    double bestDelta{};

    for(size_t i = 0; i < s.sequencia.size() - 3; i++){
        size_t vi = s.sequencia[i];
        size_t vi_next = s.sequencia[i + 1];
        for(size_t j = i + 2; j < s.sequencia.size() - 1; j++){
            size_t vj = s.sequencia[j];
            size_t vj_next = s.sequencia[j + 1];

            double delta =  
            - tsp_info.getDistance(vi, vi_next)
            - tsp_info.getDistance(vj, vj_next)
            + tsp_info.getDistance(vi, vj)
            + tsp_info.getDistance(vi_next, vj_next);

            if(delta < bestDelta){
                bestDelta = delta;
                best_i = i;
                best_j = j;
                
            }
        }
    }

    if(bestDelta < 0){
        reverse(s.sequencia.begin() + best_i + 1, s.sequencia.begin() + best_j + 1);
        s.valorObj += bestDelta;
        return true;
    }
    return false;
}

void BuscaLocal(Solucao& s, Data& tsp_info){
    vector <int> NL = {1, 2, 3, 4, 5};
    bool improved = false;

    while(NL.empty() == false)
    {
        int n = rand() % NL.size();
        switch(NL[n])
        {
        case 1:
            improved =  bestImprovementSwap(s, tsp_info);
            break;
        case 2:
            improved = bestImprovement2Opt(s, tsp_info);
            break;
        case 3:
            improved = bestImprovementOrOpt(s, tsp_info, 1);
            break;
        case 4:
            improved = bestImprovementOrOpt(s, tsp_info, 2);
            break;
        case 5:
            improved = bestImprovementOrOpt(s, tsp_info, 3);
            break;
        }
        if (improved)
            //admite todas as estruturas como opçoes novamente já que a soluçao mudou
            NL = {1, 2, 3, 4, 5};
        else
            //descarta a estrutura de vizinhança sorteada como opçao na proxima execuçao
            NL.erase(NL.begin() + n);
    }
}

Solucao Perturbacao(Solucao& s, Data& tsp_info){
    Solucao s_linha = s;
    
    //tamanho maximo de um bloco
    size_t max = (size_t)ceil(tsp_info.getDimension()/10.0);
    //tamanho maximo entre os gaps


    //tamanho dos blocos
    size_t A = rand() % (max - 1) + 2;
    size_t B = rand() % (max - 1) + 2;

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

Solucao ILS(int& maxIter, int& maxIterILS, Data& tsp_info){
    Solucao bestOfAll;
    bestOfAll.valorObj = INFINITY;
    for(int i = 0; i < maxIter; i++){
        Solucao s = Construcao(tsp_info);
        Solucao best = s;

        int iterIls = 0;

        while(iterIls <= maxIterILS){
            BuscaLocal(s, tsp_info);
            if(s.valorObj < best.valorObj){
                best = s;
                iterIls = 0;
            }
            s = Perturbacao(best, tsp_info);
            iterIls++;
        }
        if(best.valorObj < bestOfAll.valorObj)
            bestOfAll = best;
    }

    return bestOfAll;
}