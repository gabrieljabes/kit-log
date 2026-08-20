#include "OneTree.h"
#include "Data.h"


OneTree solve1Tree(Data& tsp_info, vector<double>& lambda){
    int dim = tsp_info.getDimension();
    vector<vector<double>> custos_linha(dim, vector<double>(dim));
    //- melhores distancias
    double menorCusto = INT_MAX;
    double sec_menorCusto = INT_MAX - 1;
    int best_j = -1;
    int sec_best_j = -1;


        for(int i = 0; i < dim; i++){
            for(int j = i + 1; j < dim; j++){
                custos_linha[i][j] = tsp_info.getDistance(i + 1, j + 1) - lambda[i] - lambda[j];
                custos_linha[j][i] = custos_linha[i][j];
            }
        }
        for(int j = 1; j < dim; j++){
            custos_linha[0][j] = tsp_info.getDistance(1, j + 1) - lambda[0] - lambda[j];

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

    for(int i = 0; i < tree.edges.size(); i++)
        nodes_degree.insert({i, 0});
        
    for(int i = 0; i < tree.edges.size(); i++){
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
    for(int i = 0; i < dim; i++){
        max_degree = max(max_degree, tree.degree[i]);
        min_degree = min(min_degree, tree.degree[i]);
    }
    if(max_degree == 2 && min_degree == 2)
        tree.is_tour = true;
    
    return tree;

}


OneTree SubgradientMethod(double& ub, Data& tsp_info){
    int dim = tsp_info.getDimension();
    double epsilon_min = pow(10, -5);
    int k_max = 30;
    
    int k = 0;
    double epsilon = 1;// w*
    double u;
    vector<double> lambda(dim, 0);
    OneTree best_tree;

    while(epsilon > epsilon_min && !best_tree.is_tour){
        OneTree tree = solve1Tree(tsp_info, lambda);

        if(tree.LB > best_tree.LB){
            best_tree = tree;
            k = 0;
        } else{
            k+= 1;
            if(k >= k_max){
                k = 0;
                epsilon /= 2;
            }
        }
        // somatorio dos nos
        double sum = 0;
        for(int i = 0; i < dim; i++)
            sum += pow((2 - tree.degree[i]), 2);

        u = epsilon*((ub - tree.LB)/sum);
        for(int i = 0; i < dim; i++)
            lambda[i] += u*(2 - tree.degree[i]);

    cout << "LB=" << tree.LB << " arestas=" << tree.edges.size() << endl;
    for(auto &e : tree.edges) cout << e.first + 1 << "-" << e.second + 1<< endl;
    for(int i = 0; i < dim; i++) cout << "grau[" << i << "]=" << tree.degree[i] << endl;

    }
    return best_tree;
}       
