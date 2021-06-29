/*

    1. Letter Case Permutation

    Given a string s, we can transform every letter individually to be lowercase or uppercase to create another string.
    Return a list of all possible strings we could create.

*/

class Solution {
public:
    vector<string> ans;

    void DFS(string &s, int index) {
        int n = s.size();

        if (n == index) {
            ans.push_back(s);
            return;
        }

        DFS(s, index + 1);
        char temp = s[index];

        // if(isalpha(s[index]))
        //     s[index] ^= 1 << 5 ;

        if (s[index] <= 'z' && s[index] >= 'a')
            s[index] -= 32;
        else if (s[index] <= 'Z' && s[index] >= 'A')
            s[index] += 32;
        else
            return;

        DFS(s, index + 1);
        s[index] = temp;
    }

    vector<string> letterCasePermutation(string s) {
        if (s == "")
            return ans;

        DFS(s, 0);

        return ans;
    }
};