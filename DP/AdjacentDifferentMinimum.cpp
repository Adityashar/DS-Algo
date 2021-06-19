// https://assessment.hackerearth.com/challenges/hiring/amazon-sde-hiring-challenge-2/algorithm/samu-and-shopping-165-5691d19b/
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

pl getMin(vector<int> &v){
    if(v[0] <= v[1] && v[0] <=v[2]) return {v[0], 0};
    else if(v[1] <= v[0] && v[1] <=v[2]) return {v[1], 1};
    else return {v[2], 2};
}

int main(){
    ll t, m;
    cin>>t;
    rep(c, 0, t){
        ll n; 
        cin>>n;
        vector<vector<int>> v;
        rep(i, 0, n){
            int x, y, z;
            cin>>x>>y>>z;
            v.pb({x, y, z});
        }
        vector<ll> dp1(n), dp2(n), dp3(n);
        dp1[0] = v[0][0], dp2[0] = v[0][1], dp3[0] =  v[0][2];
        rep(i, 1, n){
            dp1[i] = min(dp2[i-1], dp3[i-1]) + v[i][0];
            dp2[i] = min(dp1[i-1], dp3[i-1]) + v[i][1];
            dp3[i] = min(dp2[i-1], dp1[i-1]) + v[i][2];
        }
        cout<<min(dp1[n-1], min(dp2[n-1], dp3[n-1]))<<endl;
    } 
}