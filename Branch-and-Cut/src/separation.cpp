#include "separation.h"

vector <vector<int> > MaxBack(double** x, int n){
    vector<vector<int>> cut_sets;
    vector<bool> cut_node(n);

    for(int k = 0; k < n; k++){
        if(cut_node[k] == true)
            continue;
        vector<bool> S_group(n);
        vector<bool> best_S(n);
        vector<double> w(n, 0); 
        vector<int> cut_set;
        int last_visited = k;

        double min_cut = 99999999;

        for(int i = 0; i < n - 1; i++){
            if(i == 0)
                S_group[k] = true;
            
            int best_edge_index = last_visited;
            double best_edge = -1;

            for(int j = 0; j < w.size(); j++){
                if(last_visited > j)
                    w[j] += x[j][last_visited];
                else
                    w[j] += x[last_visited][j];
                if(w[j] > best_edge && S_group[j] == false){
                    best_edge = w[j];
                    best_edge_index = j;
                }
            }

                double cut = 0;
                for(int j = 0; j < w.size(); j++){
                    if(S_group[j])
                        continue;
                    cut += w[j]; 
                }

                if(min_cut > cut){
                    min_cut = cut;
                    best_S = S_group;
                } 

                S_group[best_edge_index] = true;
                last_visited = best_edge_index;
        }
        
        for(int j = 0; j < n; j++)
            if(best_S[j])
                cut_set.push_back(j);

        if(min_cut < 2.0 - EPSILON){
            cut_sets.push_back(cut_set);
            for(int c : cut_set)
                cut_node[c] = true;
        }
    }

    
    return cut_sets;

}
vector <vector<int> > MinCut(double** x, int n){
    vector<vector<int>> a;
    return a;
}
