// { Driver Code Starts
#include<bits/stdc++.h>
using namespace std;

int maximizeTheCuts(int n, int x, int y, int z);

int main() {
    
    //taking testcases
    int t;
    cin >> t;
    while(t--)
    {
        //taking length of line segment
        int n;
        cin >> n;
        
        //taking types of segments
        int x,y,z;
        cin>>x>>y>>z;
        
        //calling function maximizeTheCuts()
        cout<<maximizeTheCuts(n,x,y,z)<<endl;

    }

	return 0;
}// } Driver Code Ends

int solve(int n, vector<int> &v, vector<int> &dp){
    int val = INT_MIN;
    if(n < 0) return INT_MIN;
    if(n == 0) return 0;
    if(dp[n] != -1) return dp[n];
    
    for(int i=0; i<3; i++){
        int cnt = solve(n-v[i], v, dp);
        if(cnt != INT_MIN){
            val = max(cnt + 1, val);
        }
    }
    dp[n] = val;
    return val;
}

//Complete this function
int maximizeTheCuts(int n, int x, int y, int z)
{
    //Your code here
    vector<int> dp(n+1, -1);
    vector<int> v = {x, y, z};
    int ans = solve(n, v, dp);
    
    return ans<=0?0:ans;
}