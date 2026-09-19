#include "separation.h"

typedef struct{
    vector<int> order;
    vector<double> cuts; 
} Phase;


Phase InnerMaxBack(double** x, vector<bool> active, int start, int n){
    Phase phase;

    int last_visited = start;
    vector<double> maxback_val(n, 0);
    vector<bool> s_group(n);
    
    phase.order.push_back(start);
    for(int i = 0; i < n - 1; i++){
        if(i == 0)
            s_group[start] = true;
        
        int best_edge_index = start;
        double best_edge = -1;

        for(int j = 0; j < maxback_val.size(); j++){
            if(last_visited > j)
                maxback_val[j] += x[j][last_visited];
            else
                maxback_val[j] += x[last_visited][j];
            if(maxback_val[j] > best_edge && s_group[j] == false){
                best_edge = maxback_val[j];
                best_edge_index = j;
            }
        }

        double cut = 0;
        for(int j = 0; j < maxback_val.size(); j++){
            if(s_group[j])
                continue;
            cut += maxback_val[j]; 
        }

        phase.cuts.push_back(cut);
        phase.order.push_back(best_edge_index);
        last_visited = best_edge_index;
        s_group[best_edge_index] = true;
    }

    return phase;
}


Phase InnerMaxBack2(vector<vector<double>>& x, vector<bool> G, int start, int n){

    Phase phase;
    int last_visited = start;
    vector<double> maxback_val(n, 0);   
    vector<bool> s_group(n);

    int lack = 1;
    for(auto e : G)
        if(!e)
            lack++;

    phase.order.push_back(start);
    for(int i = 0; i < n - lack; i++){
        if(i == 0)
            s_group[start] = true;
        
        int best_edge_index = start;
        double best_edge = -1;

        for(int j = 0; j < maxback_val.size(); j++){
            if(!G[j])
                continue;
            if(last_visited > j)
                maxback_val[j] += x[j][last_visited];
            else
                maxback_val[j] += x[last_visited][j];
            if(maxback_val[j] > best_edge && s_group[j] == false){
                best_edge = maxback_val[j];
                best_edge_index = j;
            } 
        }

        double cut = 0;
        for(int j = 0; j < maxback_val.size(); j++){
            if(s_group[j])
                continue;
            cut += maxback_val[j]; 
        }

        phase.cuts.push_back(cut);
        phase.order.push_back(best_edge_index);

        last_visited = best_edge_index;
        s_group[best_edge_index] = true;
    }

    return phase;
}

        

vector <vector<int> > MaxBack(double** x, int n){
    vector<vector<int>> cut_sets;
    vector<bool> cut_node(n);
    vector<bool> actives(n, 1);
    double best_min_cut = 9999999;

    for(int k = 0; k < n; k++){
        if(cut_node[k] == true)
            continue;

        Phase p = InnerMaxBack(x, actives, k, n);
        
        auto min_cut_it = min_element(p.cuts.begin(), p.cuts.end());
        int min_cut_index = min_cut_it - p.cuts.begin();
        double min_cut = p.cuts[min_cut_index];
        
        vector<int> cut_set;

        for(int i = 0; i < min_cut_index + 1; i++)
            cut_set.push_back(p.order[i]);

        if(min_cut < 2.0 - EPSILON && min_cut <= best_min_cut){
            for(auto& p : cut_set)
                cut_node[p] = true;
            best_min_cut = min_cut;
            cut_sets.push_back(cut_set);
        }   
    }

    return cut_sets;
}

vector <vector<int> > MinCut(double** x, int n){
    vector<vector<double>> x_costs(n, vector<double>(n));
    for(int i = 0; i < n; i++){
        for(int j = i+1; j < n; j++){
            x_costs[i][j] = x[i][j];
            x_costs[j][i] = x_costs[i][j];
        }
    }

    vector<vector<int>> cut_sets;
    vector<bool> active(n, 1);
    vector<vector<int>> nodes(n);

    for(int i = 0; i < n; i++) 
        nodes[i] = {i};

    for(int i = 0; i < n - 1; i++){
        Phase p = InnerMaxBack2(x_costs, active, 0, n);

        int s = p.order[p.order.size() - 2]; //penultimo
        int t = p.order[p.order.size() - 1]; // ultimo

        double cut = p.cuts.back();

        if(cut < 2.0 - EPSILON){
            cut_sets.push_back(nodes[t]);
        }

        active[t] = false;

        for(int i = 0; i < nodes[t].size(); i++)
            nodes[s].push_back(nodes[t][i]);
        
        nodes[t].clear();

        for(int j = 0; j < n; j++){
            if(!active[j])
                continue;
            x_costs[s][j] += x_costs[t][j];
            x_costs[j][s] = x_costs[s][j];
        }

    }
    return cut_sets;
}
