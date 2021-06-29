#include<bits/stdc++.h>
using namespace std;

#define pp pair<int, int>
#define f first
#define s second


int main() {
	int t;
	cin >> t;

	while (t--) {
		int n;
		cin >> n;

		vector<pp> v;

		for (int i = 0; i < n; i++) {
			int x;
			cin >> x;
			v.push_back({x, i});
		}

		sort(v.begin(), v.end());

		long long ans = 0, k = 2 * n;

		int l = 0, r = n - 1;

		while (l < r) {
			if (1LL * v[l].f * v[r].f <= k) {

				int i = r;
				while (i > l) {
					if (v[l].s + v[i].s + 2 == v[l].f * v[i].f)
						ans += 1;
					i--;
				}

				// ans += r - l;
				l++;
			}
			else
				r--;
		}

		cout << ans << endl;

	}

	return 0;
}