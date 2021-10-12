// Rabin Karp

int q = 1019;
int d = 256;

class Solution {
public:

	int generate(string &s, int n) {
		int hash = 0;

		for (int i = 0; i < n; i++) {
			hash = (d * hash + s[i]) % q;
		}

		return hash;
	}

	bool eq(string &t, string &s, int start) {
		int i = 0;

		while (i < t.size()) {
			if (t[i] != s[start])
				return false;
			i++, start++;
		}

		return true;
	}

	int strStr(string s, string t) {
		int n = s.size();
		int m = t.size();
		int h = 1;

		for (int i = 0; i < m - 1; i++)
			h = (h * d) % q;

		if (m == 0)
			return 0;

		if (n < m)
			return -1;

		int tHash = generate(t, m);
		int sHash = generate(s, m);

		for (int i = 0; i < n - m + 1; i++) {
			if (tHash == sHash && eq(t, s, i))
				return i;

			if (i != n - m) {
				sHash = (d * (sHash - h * s[i]) + s[i + m]) % q;

				if (sHash < 0)
					sHash += q;
			}
		}

		return -1;
	}
};