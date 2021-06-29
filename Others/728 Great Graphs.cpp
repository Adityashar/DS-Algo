#include<bits/stdc++.h>
using namespace std;

int main() {
	int t;
	cin >> t;

	while (t--) {
		int n;
		cin >> n;

		vector<int> v;
		for (int i = 0; i < n; i++) {
			int x; cin >> x;
			v.push_back(x);
		}

		sort(v.begin(), v.end());

		long long ans = 0;
		long long prefix = 0;

		for (int i = 1; i < n; i++) {
			ans += prefix - 1LL * v[i] * i;
			prefix += v[i];
		}

		ans += v.back();

		cout << ans << endl;
	}

	return 0;
}