/*
    1. Palindrom Partitioning I
    Given a string s, partition s such that every substring of the partition is a palindrome. Return all possible palindrome partitioning of s.
*/


class Solution {
public:
    vector<vector<string>> ans;

    bool prefixPalin(string &P, int s, int e) {
        while (s < e)
            if (P[s++] != P[e--])
                return false;
        return true;
    }

    void DFS(string &s, vector<string> &p, int index) {
        int n = s.size();

        if (index == n) {
            ans.push_back(p);
            return;
        }

        for (int i = index; i < n; i++) {
            if (prefixPalin(s, index, i)) {
                p.push_back(s.substr(index, i - index + 1));
                DFS(s, p, i + 1);
                p.pop_back();
            }
        }
    }

    vector<vector<string>> partition(string s) {
        int n = s.size();
        vector<string> partition;

        if (n == 0)
            return ans;

        DFS(s, partition, 0);

        return ans;
    }
};