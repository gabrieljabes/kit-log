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
    {0.0, 0.75,  0.0, 0.75,  0.0, 0.25, 0.25,  0.0},  // E
    {0.0,  0.0,  0.0,  0.0, 0.25,  0.0, 0.75,  1.0},  // F
    {0.0,  0.0,  0.0,  0.0, 0.25, 0.75,  0.0,  1.0},  // G
    {0.0,  0.0,  0.0,  0.0,  0.0,  1.0,  1.0,  0.0}   // H
};

    //for (int i = 0; i < n; i++)
    // vai testar com todos os nos
        int n = edges.size();
        vector<bool> S_group(n);
        //0 -> i 
        int inicio = 0;
        int fim;
        S_group[inicio] = true;


        for(int i = 0; i < n - 1; i++){
            double best_edge = 0;
            int best_node_index = -1;
            double cut = 0;

            for(int j = 0; j < n; j++){
                if(S_group[j] == true)
                    continue;

                if(edges[inicio][j] >= best_edge){
                    best_edge = edges[inicio][j];
                    best_node_index = j;
                }
            }

            S_group[best_node_index] = true;
            fim = best_node_index;

            for(int j = 0; j < n ;j++){
                if(S_group[j])
                    continue;
                for(int k = 0; k < n; k++){
                    if(S_group[k])
                        cut+= edges[j][k];
                }
            }
            
            cout << "corte: " << cut << endl;
            cout << "inicio: " << inicio << endl;
            cout << "fim: " << fim << endl;
            cout << endl;

        }


    return 0;

}