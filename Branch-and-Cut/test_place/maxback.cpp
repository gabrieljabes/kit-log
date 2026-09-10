#include <bits/stdc++.h>

using namespace std;
#define EPSILON 0.00000001

int main(){

std::vector<std::vector<double>> edges = {
//    A     B     C     D     E     F     G     H
    {0.0,  1.0, 0.75, 0.25,  0.0,  0.0,  0.0,  0.0},  // A
    {1.0,  0.0, 0.25,  0.0, 0.75,  0.0,  0.0,  0.0},  // B
    {0.75, 0.25, 0.0,  1.0,  0.0,  0.0,  0.0,  0.0},  // C
    {0.25, 0.0,  1.0,  0.0, 0.75,  0.0,  0.0,  0.0},  // D
    {0.0, 0.75,  0.0, 0.75,  0.0, 0.25, 0.25,  0.0},        // E
    {0.0,  0.0,  0.0,  0.0, 0.25,  0.0, 0.75,  1.0},  // F
    {0.0,  0.0,  0.0,  0.0, 0.25, 0.75,  0.0,  1.0},  // G
    {0.0,  0.0,  0.0,  0.0,  0.0,  1.0,  1.0,  0.0}   // H
};

    int n = edges.size();
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
                w[j] += edges[last_visited][j];
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

    for(int i = 0; i < cut_sets.size(); i++){
        for(int j = 0; j < cut_sets[i].size(); j++){
            cout << cut_sets[i][j] << " ";
        }
        cout << endl;
    }

    return 0;

}