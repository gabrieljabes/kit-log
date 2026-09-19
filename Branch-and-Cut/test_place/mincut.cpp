#include <algorithm>
#include <bits/stdc++.h>
#include <cstddef>
#include <ostream>

using namespace std;
#define EPSILON 0.00000001

typedef struct{
    vector<int> order;
    vector<double> cuts; 
} Phase;


void debug(Phase& p){
    cout << "order and cuts" << endl;
    for(auto& e : p.order)
        cout << e << " ";
    cout << endl;
    for(auto& e : p.cuts)
        cout << e << " ";
    cout << endl;
    cout << endl;
}

Phase InnerMaxBack(vector<vector<double>>& x, vector<bool> G, int start, int n){

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



int main(){
/*
    vector<vector<double>> w2= {
        {0,  9,  0, 12, 11,  0},
        {9,  0,  4,  0,  9,  0},
        {0,  4,  0,  0, 18,  7},
        {12, 0,  0,  0,  0,  0},
        {11, 9, 18,  0,  0, 11},
        {0,  0,  7,  0, 11,  0}
    };
*/
    vector<vector<double>> edges = {
    {0,   1,   0.5, 0.5, 0,   0  },
    {1,   0,   1,   0,   0,   0  },
    {0.5, 1,   0,   0,   0,   0.5},
    {0.5, 0,   0,   0,   1,   0.5},
    {0,   0,   0,   1,   0,   1  },
    {0,   0,   0.5, 0.5, 1,   0  }
};

/*
    vector<vector<double>> edges = {
        {0,  20,  25, 0},
        {20,  0,  8,  10},
        {25,  8,  0,  18},
        {0, 10,  18,  0},
    };
*/
    int n = edges.size();
    
        vector<vector<double>> x_costs(n, vector<double>(n));
            for(int i = 0; i < n; i++){
                for(int j = i+1; j < n; j++){
                    x_costs[i][j] = edges[i][j];
                    x_costs[j][i] = x_costs[i][j];
                }
            }

        vector<vector<int>> cut_sets;
     
        double best_min_cut = 9999999;
        vector<bool> active(n, 1);
        vector<vector<int>> nodes(n);

         for(int i = 0; i < n; i++) 
            nodes[i] = {i};

        for(int i = 0; i < n - 1; i++){
            Phase p = InnerMaxBack(x_costs, active, 0, n);

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


    return 0;

}