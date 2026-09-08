#include <bits/stdc++.h>
#include <iterator>

using namespace std;

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

    //for (int i = 0; i < n; i++)
    // vai testar com todos os nos
        int n = edges.size();
        vector<bool> S_group(n);

        vector<double> w(n, 0);
        //0 -> i 
        int inicio = 0;
        double cut;


        S_group[0] = true;
        int last_visited = 0;
        for(int i = 0; i < n; i++){

            int best_edge_index;
            double best_edge = 0;

            cout << " ==== iteraçao " << i << endl;
            for(int j = 0; j < w.size(); j++){
                if(S_group[j])
                    continue;
                w[j] += edges[last_visited][j];
                if(w[j] > best_edge && S_group[j] == false){
                    best_edge = w[j];
                    best_edge_index = j;
                }
            }
            double sum = 0;
            for(int j = 0; j < w.size(); j++){
                if(S_group[j])
                    continue;
                sum += w[j]; 
            }

            if(sum < 2){
                cut = sum;
                break;
            } else{
                S_group[best_edge_index] = true;
                last_visited = best_edge_index;
            }

            cout << "w=" << endl;
            for(auto &e : w)
                cout << e << " ";
            cout << endl << endl;


        
            cout << "soma=" << sum << endl;
        }

        cout << "cut=" << cut << endl;

    return 0;

}

