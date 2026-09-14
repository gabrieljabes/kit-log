#include "separation.h"

Phase InnerMaxBack(double** x, int start, int n){
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
        

vector <vector<int> > MaxBack(double** x, int n){
     vector<vector<int>> cut_sets;
    vector<bool> cut_node(n);
    double best_min_cut = 9999999;

    for(int k = 0; k < n; k++){
        if(cut_node[k] == true)
            continue;

        Phase p = InnerMaxBack(x , k, n);
        

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
    vector<vector<int>> a;
    return a;
}
