#include<bits/stdc++.h>
using namespace std;

#define ll long long


int main() {

	int t;
	cin >> t;

	while (t--) {
		ll n; cin >> n;

		priority_queue < ll, vector <ll>, greater<ll>> pq;

		for (ll i = 0; i < n; i++) {
			ll x; cin >> x;
			pq.push(x);
		}

		ll cost = 0;

		while (pq.size() > 1) {
			ll sum = 0;
			sum += pq.top(); pq.pop();
			sum += pq.top(); pq.pop();

			cost += sum;
			pq.push(sum);
		}

		cout << cost << endl;

	}
	return -1;
}