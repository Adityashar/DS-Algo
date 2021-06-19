// """
// For Each Number calculate the given F(X) 
// Sum the value in the range [L, R]

// For this we can maintain a digit DP[] : Length , Tight, previous digit
// Each DP[L, T, P] = Sum of F[X] for all X having length L

// Each num can start with any of the digits [0, UB], add its contribution to the DP value if prev != cur
// val += count_of_numbers_starting_with_X(X) * X * 10 ^(position - 1) + RECUR(n-1, T, X);

// cout<<(ansR + mod - ansL + bruteForce(L, l))%mod;
// modulo remainder of L might be greater than R even when the actual F(R) remails higher than F(L)

// """
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
using namespace std;

ll Pow[100001];

void power(){
    Pow[0] = 1;
    for(int i=1; i<=100000; i++) Pow[i] = (Pow[i-1] * 10) % mod;
}

ll power10(ll i){
    return Pow[i];
}

ll countDP[100003][2];

ll count(string &S, ll n, bool tight){
    if(tight == 0) return power10(n);
    if(n == 0) return 1;
    if(countDP[n][tight] != -1) return countDP[n][tight];
    ll ans = 0;

    int UB = S[S.length() - n] - '0';
    for(int i=0; i<=UB; i++){
        ans = (ans + count(S, n-1, UB == i)) % mod;
    }

    return countDP[n][tight] = ans % mod;
}

ll dp[100005][11][2];

ll solveDigit(string &S, ll n, bool tight, int prev){
    if(n == 0){
        return 0;
    }

    if(dp[n][prev][tight] != -1) return dp[n][prev][tight];

    ll ans = 0;
    int UB = (tight == 1)? (S[S.length() - n] - '0'): 9;

    for(int i=0; i<=UB; i++){
        if(prev != i) 
            ans = (ans + (count(S, n-1, tight & (UB == i)) * i * power10(n-1))%mod) % mod;

        ans = (ans + solveDigit(S, n-1, tight & (UB == i), i)) % mod;
    }

    return dp[n][prev][tight] = ans % mod;
}

string findDiff(string &str1, ll &n1)
{
    string str = "", str2 = "1";

    ll n2 = 1;
    ll diff = n1 - n2;
    int carry = 0;
 
    for (int i = n2 - 1; i >= 0; i--) {
        ll sub = ((str1[i + diff] - '0') - (str2[i] - '0') - carry);
        if (sub < 0) {
            sub = sub + 10;
            carry = 1;
        }
        else
            carry = 0;

        str.push_back(sub + '0');
    }

    for (ll i = n1 - n2 - 1; i >= 0; i--) {
        if (str1[i] == '0' && carry) {
            str.push_back('9');
            continue;
        }
        ll sub = ((str1[i] - '0') - carry);
        if (i > 0 || sub > 0) // remove preceding 0's
            str.push_back(sub + '0');
        carry = 0;
    }
 
    reverse(str.begin(), str.end());
    return str;
}
int bruteForce(string& L, int nl){
    int prev_dig = 10;
    ll res = 0;
    for(int i = 0; i < L.length(); i++){
        if((L[i] - '0') != prev_dig){
            res = (res + (L[i] - '0') * power10(L.length() - i - 1)) % mod;
        }
        prev_dig = (L[i] - '0');
    }
    return res % mod;
}
int main(){
    fast_io;
    power();
    int t; cin>>t;
    rep(c, 0, t){
        string L, R;
        ll l, r;
        cin>>l>>L>>r>>R;

        // L = findDiff(L, l);
        // l = L.length();
        // cout<<L<<endl;
        memset(countDP, -1, sizeof(countDP));
        memset(dp, -1, sizeof(dp));

        ll ansR = solveDigit(R, r, 10, -1);

        memset(countDP, -1, sizeof(countDP));
        memset(dp, -1, sizeof(dp));

        ll ansL = solveDigit(L, l, 10, -1);

        cout<<ansR<<" "<<ansL<<endl;
        cout<<(ansR + mod - ansL + bruteForce(L, l))%mod;
        cout<<endl;
    }
}