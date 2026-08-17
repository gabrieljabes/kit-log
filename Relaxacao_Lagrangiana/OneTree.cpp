#include "OneTree.h"


OneTree solve1Tree(vector<vector<double>>& costs, vector<double>& lambda){
    int dim = costs.size();
    vector<vector<double>> custos_linha(dim, vector<double>(dim));
    //- melhores distancias
    double menorCusto = INT_MAX;
    double sec_menorCusto = INT_MAX - 1;
    int best_j;
    int sec_best_j;


        for(int i = 0; i < dim; i++){
            for(int j = i + 1; j < dim; j++){
                custos_linha[i][j] = costs[i][j] - lambda[i] - lambda[j];
                custos_linha[j][i] = custos_linha[i][j];
            }
        }
        for(int j = 1; j < dim; j++){
            custos_linha[0][j] = costs[0][j] - lambda[0] - lambda[j];

            if(menorCusto >= custos_linha[0][j]){
                sec_menorCusto = menorCusto;
                sec_best_j = best_j;
                menorCusto = custos_linha[0][j];
                best_j = j;
            } else if(menorCusto <= custos_linha[0][j] && sec_menorCusto >= custos_linha[0][j]){
                sec_menorCusto = custos_linha[0][j];
                sec_best_j = j;
            }
        }

    Kruskal k(custos_linha);
    OneTree tree;

    int qtd_nodes = custos_linha.size();
    k.MST(qtd_nodes);
    tree.edges = k.getEdges();

    tree.edges.push_back(pair <int, int>(0, best_j));
    tree.edges.push_back(pair <int, int>(0, sec_best_j));

    //achando o grau dos nós
    map <int, int> nodes_degree;

    for(int i = 0; i < dim; i++)
        nodes_degree.insert({i, 0});
        
    for(int i = 0; i < dim; i++){
        nodes_degree[tree.edges[i].first]++;
        nodes_degree[tree.edges[i].second]++;
    }

    tree.degree.resize(dim);
    int index = 0;
    for(auto& g : nodes_degree){
        tree.degree[index] = g.second;
        index++;
    }

    //calculo do lb
    double lb = 0;

    for(int i = 0; i < dim; i++){
        int first_node = tree.edges[i].first;
        int second_node = tree.edges[i].second;

        lb += custos_linha[first_node][second_node] + 2*lambda[i];
    }

    tree.LB = lb;
    
    //verifica se os graus sao estritamente 2
    int max_degree = INT_MIN; int min_degree = INT_MAX;
    for(int i = 0; i < tree.degree.size(); i++){
        max_degree = max(max_degree, tree.degree[i]);
        min_degree = min(min_degree, tree.degree[i]);
    }
    if(max_degree == 2 && min_degree == 2)
        tree.is_tour = true;

    //debug print
    for(int i = 0; i < dim; i++){
        for(int j = 0; j < dim; j++)
            cout << custos_linha[i][j] << ", ";
        cout << endl;
    }
    cout << "arestas:" << endl;
    for(auto& i : tree.edges)
        cout << i.first + 1 << " " << i.second + 1 << endl;
    cout << "grau de cada nó:" << endl;
    for(int i = 0; i < dim; i++)
        cout  << "node: " << i + 1 << " degree: " << tree.degree[i] <<  endl;

    cout << "lb: " << lb << endl;
    
    return tree;

}

