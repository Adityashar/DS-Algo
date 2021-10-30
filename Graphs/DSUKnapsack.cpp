#include<bits/stdc++.h>
using namespace std;

#define ll long long

vector<ll> P, UG, VG;

ll find(ll x) {
    if(P[x] != x) 
        P[x] = find(P[x]);
    
    return P[x];
} 

bool un(ll x, ll y) {
    ll px = find(x), py = find(y);

    if(px == py)
        return true;
    
    P[px] = py;
    
    UG[px] += UG[py];
    UG[py] = 0;

    VG[px] += VG[py];
    VG[py] = 0;
}

void knapsack(vector<vector<ll>> &groups, ll B) {
    
    vector<vector<ll>> dp(groups.size()+1, vector<ll>(B+1, 0));
    
    for(int i=1; i<=groups.size(); i++) {

        for(int j=1; j<=B; j++) {

            dp[i][j] = dp[i-1][j];
            
            if(j - VG[i-1] >= 0)
                dp[i][j] = max(dp[i][j], UG[i-1] + dp[i-1][j - VG[i-1]]);
        }
    }

    cout<<dp[groups.size()][B];
}

int main() {

    ll N = 4, Q = 2, B = 17;

    vector<ll> U = {12, 9, 13, 15};
    vector<ll> V = {7, 5, 8, 11};
    vector<vector<ll>> edges;

    edges = {{1, 3}, {2, 4}};

    for(int i=0; i<N; i++)
        P.push_back(i), UG.push_back(U[i]), VG.push_back(V[i]);

    for(auto &e: edges) {
        un(e[0], e[1]);
    }

    vector<vector<ll>> groups;

    for(int i=0; i<P.size(); i++) {
        if(P[i] == i) {
            groups.push_back({UG[i], VG[i]});
        }
    }

    knapsack(groups, B);

    return 0;
}