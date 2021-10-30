## 1268. Search Suggestions System

Given an array of strings products and a string searchWord. We want to design a system that suggests at most three product names from products after each character of searchWord is typed. Suggested products should have common prefix with the searchWord. If there are more than three products with a common prefix return the three lexicographically minimums products.

    Return list of lists of the suggested products after each character of searchWord is typed.


    Input: products = ["mobile", "mouse", "moneypot", "monitor", "mousepad"], searchWord = "mouse"

                      Output: [
                        ["mobile", "moneypot", "monitor"],
                        ["mobile", "moneypot", "monitor"],
                        ["mouse", "mousepad"],
                        ["mouse", "mousepad"],
                        ["mouse", "mousepad"]
                      ]

                      Explanation: products sorted lexicographically = ["mobile", "moneypot", "monitor", "mouse", "mousepad"]
                          After typing m and mo all products match and we show user ["mobile", "moneypot", "monitor"]
                          After typing mou, mous and mouse the system suggests ["mouse", "mousepad"]

                          ````cpp

struct TN {
	bool isEnd;
	map<char, TN*> map;

	TN() {
		isEnd = false;
	}
};

class Trie {
	TN *root;

public:
	Trie() {
		root = new TN();
	}

	TN* getRoot() {
		return root;
	}

	void insert(string &s) {
		TN *cur = root;

		for (auto &c : s) {
			if (cur->map.count(c) == 0)
				cur->map[c] = new TN();

			cur = cur->map[c];
		}

		cur->isEnd = true;
	}

	void DFS(TN *root, vector<string> &ans, string &s, int &c) {
		if (root == NULL || c <= 0)
			return;

		if (root->isEnd == true) {
			c--;
			ans.push_back(s);
		}

		for (auto &i : root->map) {
			if (i.second != NULL) {
				s += i.first;
				DFS(i.second, ans, s, c);
				s.pop_back();
			}
		}

	}

	vector<string> search(string &s) {
		TN *cur = root;
		vector<string> res;

		for (auto &c : s) {
			if (cur == NULL || cur->map.count(c) == 0)
				return res;

			cur = cur->map[c];
		}

		int c = 3;
		DFS(cur, res, s, c);

		return res;
	}



};

class Solution {
public:
	vector<vector<string>> suggestedProducts(vector<string>& P, string s) {
		int n = P.size();

		sort(P.begin(), P.end());

		Trie *t = new Trie();
		for (auto i : P)
			t->insert(i);

		string temp = "";
		vector<vector<string>> ans;

		for (auto &c : s) {
			temp += c;
			vector<string> res = t->search(temp);
			ans.push_back(res);
		}

		return ans;
	}
};
















```


