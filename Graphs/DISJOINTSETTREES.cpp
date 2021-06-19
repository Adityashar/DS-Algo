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
using namespace std;

int find(vector<int> &p, int i){
    if(p[i] != i) p[i] = find(p, p[i]);
    return p[i];
}

void Union(vector<int> &p, int x, int y){
    int xp = find(p, x), yp = find(p, y);
    if(xp != yp){
        if(xp < yp) p[yp] = xp;
        else p[xp] = yp;
    }
}

int getPrime(vector<int> &A, int n){
    int prime[] = {29, 31, 37, 41, 43, 47};
    int cnt = 0;
    for(int i: A){
        if(i == 43) cnt++;
    }
    if(cnt == n) return 47;
    else return 43;
}

int main(){
    fast_io;
    int t;
    cin>>t;
    for(int ip=0; ip<t; ip++){
        int N; cin>>N;
        vector<int> A;
        for(int i = 0; i<N; i++){
            int k; cin>>k;
            A.pb(k);
        }
        vector<int> p(N, -1);
        for(int i=0; i<N; i++) p[i] = i;

        for(int i=0; i<N; i++){
            for(int j=i+1; j<N; j++){
                if(__gcd(A[i], A[j]) == 1){
                    Union(p, i, j);
                }
            }
        }
        set<int> s;
        int cnt=0;
        for(int i: p) s.insert(i);
        for(int i=0; i<N; i++) if(find(p, i) == i) cnt++;

        if(cnt == 1){
            cout<<0<<endl;
            for(int i: A) cout<<i<<" ";
        }
        else{
            cout<<1<<endl<<getPrime(A, N)<<" ";
            for(int i=1; i<N; i++) cout<<A[i]<<" ";
        }
        cout<<endl;
    }
}