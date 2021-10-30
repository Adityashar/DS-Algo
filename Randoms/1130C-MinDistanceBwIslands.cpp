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
#define f first
#define s second
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

vector<vector<ll>> mat, v;
unordered_set<pl, hash_pair> l1, l2;

int r1, c1, r2, c2;

bool DFS(int r1, int c1, unordered_set<pl, hash_pair> &l, int r2, int c2) {
    int n = mat.size();

    if(r1 == r2 && c1 == c2)
        return true;

    l.insert({r1, c1});
    v[r1][c1] = 1;

    int x[] = {1,-1,0,0}, y[] = {0,0,1,-1};
    
    for(int i=0; i<4; i++) {
        int nx = x[i] + r1, ny = y[i] + c1;

        if(nx >=0 && ny >= 0 && nx < n && ny < n && !v[nx][ny] && mat[nx][ny] == 0) {
            if(DFS(nx, ny, l, r2, c2))
                return true;
        }
    }

    return false;
}


int main() {
    fast_io;

    int n; 
    cin>>n>>r1>>c1>>r2>>c2;

    r1--, c1--, r2--, c2--;

    mat.resize(n, vector<ll>(n));
    v.resize(n, vector<ll>(n, 0));

    for(int i=0; i<n; i++) {
        string temp; cin>>temp;

        for(int j=0; j<n; j++) {
            ll x = temp[j]-'0';

            mat[i][j] = x;
        }
    }


    bool ans = DFS(r1, c1, l1, r2, c2);

    if(ans) {
        cout<<"0";
    }
    else {
        ll ans = 1e13;
        DFS(r2, c2, l2, r1, c1);

        // cout<<l1.size()<<" "<<l2.size()<<endl;

        for(auto i: l1) {
            for(auto j: l2) {

                ans = min(ans, (i.f-j.f)*(i.f-j.f) + (i.s-j.s)*(i.s-j.s));
            }
        }

        cout<<ans;

    }

    return 0;
}