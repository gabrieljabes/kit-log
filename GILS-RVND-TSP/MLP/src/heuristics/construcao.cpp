#include "construcao.h"

Solucao Construcao(Data& problem_info){
    int alpha = rand() % 26;
    Solucao s;
    s.sequencia = {1};
    size_t r = 1;
    vector <size_t> CL = ListaCandidatos(problem_info);
    while(!CL.empty()){
        sort(CL.begin(), CL.end(), [&](size_t i, size_t j) {
            return problem_info.getDistance(r, i) < problem_info.getDistance(r, j);
        });

        int limite = ceil((alpha/100.0) * CL.size());
        if(limite < 1) 
            limite = 1;

        int pos_c = rand() % limite;
        size_t c = CL[pos_c];
        s.sequencia.push_back(c);
        r = c;
        CL.erase(CL.begin() + pos_c);
    }

    s.sequencia.push_back(1);

    return s;
}

vector<size_t> ListaCandidatos(Data& problem_info){
    size_t n = problem_info.getDimension();
    vector<size_t> vertices(n-1); //igonra o vertice 1
    for(int i = 0; i < n - 1; i++)
        vertices[i] = i + 2; 

    return vertices;
}
