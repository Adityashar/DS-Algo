#include<bits/stdc++.h>
#define ll long long
#define pb push_back
#define fr(a,b) for(int i = a; i < b; i++)
#define rep(i,a,b) for(int i = a; i < b; i++)
#define mod 1000000007 
#define inf (1LL<<60)
#define all(x) (x).begin(), (x).end()
#define prDouble(x) cout << fixed << setprecision(10) << x
#define triplet pair<ll,pair<ll,ll>>
#define fast_io ios_base::sync_with_stdio(false);cin.tie(NULL)
#define pl pair<ll, ll> 
#define pp pair<int, int>
#define rev(str) reverse(str.begin(), str.end())
#define repMAP(map, it) for(auto it = map.begin(); it != map.end(); it++)
#define begEnd(it) it.begin(), it.end()
#define sort(v) sort(v.begin(), v.end())
using namespace std;

struct hash_pair { 
    template <class T1, class T2> 
    size_t operator()(const pair<T1, T2>& p) const
    { 
        auto hash1 = hash<T1>{}(p.first); 
        auto hash2 = hash<T2>{}(p.second); 
        return hash1 ^ hash2; 
    } 
};


void DFS(vector<vector<int>> &adj, vector<int> &v, int s) {
    v[s] = 1;
    for(int i=0; i<adj[s].size(); i++) {
        if(adj[s][i] && v[i] == 0) {
            DFS(adj, v, i);
        }
    }
}

int main() {
    fast_io;

    int n, m; 
    cin>>n>>m;

    vector<vector<int>> lang(n);
    vector<vector<int>> adj(m, vector<int>(m, 0));

    vector<int> v(m, -1);

    int cnt = 0, sz = 0;

    for(int i=0; i<n; i++) {
        int x; cin>>x;

        if(x == 0)
            sz += 1;

        for(int j=0; j<x; j++) {
            int k; cin>>k;

            lang[i].push_back(k-1);
            v[k-1] = 0;

            // cout<<k<<endl;
        }
        // cout<<i<<endl;

        for(int p=0; p<lang[i].size(); p++) {
            for(int q=p+1; q<lang[i].size(); q++) {
                // cout<<p<<" "<<q<<endl;

                adj[lang[i][p]][lang[i][q]] = 1;
                adj[lang[i][q]][lang[i][p]] = 1;
            }
        }
        
    }

    for(int i=0; i<m; i++) {
        if(v[i] == 0) {
            DFS(adj, v, i);
            cnt += 1;
        }
    }

    if(sz == n)
        cnt += 1;

    cout<<cnt - 1 + sz<<endl;

    return 0;
}