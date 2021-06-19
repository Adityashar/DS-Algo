/*

The n-queens puzzle is the problem of placing n queens on an n x n chessboard such that no two queens attack each other.
Given an integer n, return all distinct solutions to the n-queens puzzle. You may return the answer in any order.

( O(N*N) use the pigeonhole principle, each row can have at most one queen, so assign them row-wise instead of for all cells)

Use bitmasks pls
*/

class Solution {
public:
    vector<vector<string>> ans;

    bool check(vector<string> &chess, int x, int y) {
        int n = chess.size();

        for (int i = 0; i <= x; i++)
            if (chess[i][y] == 'Q')
                return false;

        int i = x, j = y;
        while (i >= 0 && j >= 0)
            if (chess[i--][j--] == 'Q')
                return false;

        i = x, j = y;
        while (i >= 0 && j < n)
            if (chess[i--][j++] == 'Q')
                return false;

        return true;
    }

    // use of bitmask
    // there are n rows, 2*n-1 diagonal elements
    // n <=9 =>> 26 bits
    // maintain three ints for each - col, Ldiag and Rdiag
    // For diags, the sum and diff and i & j would be same if they
    // fall on the same diag !

    void DFS(vector<string> &chess, int row, int colMask, int lMask, int rMask) {
        int n = chess.size();

        if (row == n) {
            ans.push_back(chess);
            return;
        }

        for (int i = 0; i < n; i++) {
            int curCol = (1 << i), curR = (1 << (i + row)), curL = (1 << (n - 1 - i + row));

            if (curCol & colMask || curR & rMask || curL & lMask)
                continue;

            chess[row][i] = 'Q';
            DFS(chess, row + 1, curCol | colMask,  curL | lMask, curR | rMask);
            chess[row][i] = '.';

        }
    }

    vector<vector<string>> solveNQueens(int n) {
        string temp = "";
        for (int i = 0; i < n; i++)
            temp += '.';

        vector<string> chess(n, temp);

        DFS(chess, 0);

        return ans;
    }
};