'''
Insert all the vertices into the maxheap
Take the top, update all its neighboring nodes with minimum values 
Insert them into the priority queue
Through this algorithm every selected vertex would try and reduce the node values of its adjacents
Since all vertices were added initially
eventually in the distance array we would have values which are the minimum
with respect to the same node in graph
whereas in simple dijsktra each node has min value with respect to the source
'''

#include<bits/stdc++.h>
#define ll long long
#define pb push_back
#define fr(a,b) for(int i = a; i < b; i++)
#define rep(i,a,b) for(int i = a; i < b; i++)
#define mod 998244353 
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


void print2D(vector<vector<ll>> &v){
    for(int i=0; i<v.size(); i++){
        cout<<i<<" : ";
        for(int j=0; j<v[i].size(); j++) cout<<v[i][j]<<" ";
        cout<<endl;
    }
}
vector<ll> dist;


int main(){
    ll n, m;
    cin>>n>>m; 
    vector<vector<pl>> adj(n);  
    set<pl> pq;
    rep(c, 0, m){
        ll x, y, w;
        cin>>x>>y>>w;
        adj[x-1].pb({y-1, 2*w});
        adj[y-1].pb({x-1, 2*w});
    }
    rep(c, 0, n){
        ll k; cin>>k;
        dist.pb(k);
        pq.insert({k, c});
    }

    while(pq.empty() == 0){
        ll index = pq.begin()->second;
        pq.erase(pq.begin());

        for(int i=0; i<adj[index].size(); i++){
        
            ll v = adj[index][i].first;
            ll wei = adj[index][i].second;
        
            if(dist[v] > dist[index] + wei){
                pq.erase({dist[v], v});
                dist[v] = dist[index] + wei;
                pq.insert({dist[v], v});
            }
        }
    }
    
    for(ll i: dist) cout<<i<<" ";

}