#include <bits/stdc++.h>
typedef long long ll;

using namespace std;

class Subgradient{
    public:
        double ub; // ub dado por meios heuristicos
        double epsilon;
        ll k;
        ll m, n;
        vector<double> c; // vetor >>linha<< de custos 1xn
        vector <vector <double>> A; // matriz de restricoes mxn
        vector <double> b; // lado direito das restri;oes mx1
        vector <double> lambda;  // 1xm (para que lambda*(b - Ax) de 1x1)
    
    Subgradient(ll lower_bound, vector <double> costs, vector <vector <double>> restrictionsA, vector <double> restrictionsB)
    : ub(lower_bound), c(costs), A(restrictionsA), b(restrictionsB) {
        m = A.size();
        n = A[0].size();
        lambda = vector <double> (m, 0);
        k = 0;
        epsilon = 1;
    }
};

int main(){}