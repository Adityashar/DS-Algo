#include<bits/stdc++.h>
using namespace std;


int atmostB(vector<int> &A, int k) {
    if(k < 0)
        return 0;

    int n = A.size(), ws = 0, we = 0;
    int cnt = 0, odds = 0;

    while(we < n) {
        if(A[we++] % 2)
            odds++;
        
        while(ws < we && odds > k) {
            if(A[ws++] % 2)
                odds--;
        }
        cnt += we - ws;
    }

    return cnt;
}

int solve(vector<int> &A, int B) {
    int n1 = atmostB(A, B);
    int n2 = atmostB(A, B-1);

    cout<<n2<<" "<<n1<<endl;

    return n1 - n2;
}

int main() {

	vector<int> v = {5, 6, 7, 8, 9};
	cout << solve(v, 3);

	return 0;
}