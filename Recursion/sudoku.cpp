/*

    Determine if a 9 x 9 Sudoku board is valid. Only the filled cells need to be validated according to the following rules:
    Each row must contain the digits 1-9 without repetition.
    Each column must contain the digits 1-9 without repetition.
    Each of the nine 3 x 3 sub-boxes of the grid must contain the digits 1-9 without repetition.

    Input: board =
    [["8","3",".",".","7",".",".",".","."]
    ,["6",".",".","1","9","5",".",".","."]
    ,[".","9","8",".",".",".",".","6","."]
    ,["8",".",".",".","6",".",".",".","3"]
    ,["4",".",".","8",".","3",".",".","1"]
    ,["7",".",".",".","2",".",".",".","6"]
    ,[".","6",".",".",".",".","2","8","."]
    ,[".",".",".","4","1","9",".",".","5"]
    ,[".",".",".",".","8",".",".","7","9"]]
    Output: false
    Explanation: Same as Example 1, except with the 5 in the top left corner being modified to 8.
    Since there are two 8's in the top left 3x3 sub-box, it is invalid.

*/


class Solution {
public:

    bool check(vector<char> &row) {
        vector<int> cnt(10, 0);
        for (char c : row)
            if (c != '.' && ++cnt[c - '0'] == 2)
                return false;
        return true;
    }

    bool check(vector<vector<char>>& board, int r, int c) {
        vector<int> cnt(10, 0);
        for (int i = r; i < r + 3; i++) {
            for (int j = c; j < c + 3; j++) {
                char c = board[i][j];
                if (c != '.' && ++cnt[c - '0'] == 2)
                    return false;
            }
        }

        return true;
    }

    bool myWay(vector<vector<char>>& board) {
        int n = board.size();

        for (int i = 0; i < n; i++) {
            if (!check(board[i]))
                return false;

            vector<char> col;
            for (int j = 0; j < n; j++)
                col.push_back(board[j][i]);

            if (!check(col))
                return false;
        }

        for (int i = 0; i < n; i += 3) {
            for (int j = 0; j < n; j += 3) {
                if (!check(board, i, j))
                    return false;
            }
        }

        return true;
    }

    bool isValidSudoku(vector<vector<char>>& board) {
        int n = board.size();

        int rows[9][9] = {0}, cols[9][9] = {0};
        int squares[3][3][9] = {0};

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                char c = board[i][j];
                if (c == '.')
                    continue;
                int num = c - '0' - 1;
                if (rows[i][num]++ || cols[j][num]++ || squares[i / 3][j / 3][num]++)
                    return false;
            }
        }

        return true;
    }
};


/*

    Sudoku Solver

*/


class Solution {
public:
    int rs[9][9], cs[9][9], sq[3][3][9];

    // fill it row-wise
    bool DFS(vector<vector<char>>& board, int r, int c) {
        if (r == 9) // completed the last row
            return true;
        if (c == 9) // completed the last column of rth row
            return DFS(board, r + 1, 0);
        if (board[r][c] != '.') // if already filled, fill next column cell
            return DFS(board, r, c + 1);

        for (int i = 0; i < 9; i++) {
            char s = i + '1';
            if (rs[r][i] || cs[c][i] || sq[r / 3][c / 3][i]) // check if already present
                continue;

            rs[r][i] = cs[c][i] = sq[r / 3][c / 3][i] = 1;
            board[r][c] = s;

            if (DFS(board, r, c + 1))
                return true;

            board[r][c] = '.';
            rs[r][i] = cs[c][i] = sq[r / 3][c / 3][i] = 0;
        }

        return false;
    }

    void solveSudoku(vector<vector<char>>& board) {
        memset(rs, 0, sizeof(rs));
        memset(cs, 0, sizeof(cs));
        memset(sq, 0, sizeof(sq));

        int n = board.size();

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                char c = board[i][j];

                if (c == '.')
                    continue;

                int num = c - '0' - 1;
                rs[i][num] = cs[j][num] = sq[i / 3][j / 3][num] = 1;
            }
        }
        DFS(board, 0, 0);
    }
};