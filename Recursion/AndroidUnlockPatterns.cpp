#define pp pair<int,int>
#define f first
#define s second

class Solution {
public:
    int cnt, m, n;
    unordered_map<int, vector<int>> map;
    vector<vector<int>> check;

    // bool check(int i, int prev, int mask) {
    //     for(auto s: map[prev]) {
    //         int d1 = s/10, d2 = s%10;
    //         if(i == d2 && (mask & (1 << (d1-1)) == 0))
    //             return true;
    //     }
    //     return false;
    // }

    int DFS(long visited, int prev, int keys) {
        if (keys <= 0)
            return (keys == 0) ? 1 : 0;

        int ans = 0;
        visited |= 1 << prev;

        for (int i = 1; i <= 9; i++) {
            // if((visited & (1 << i)) || (check[i][prev] != 0 && !(visited & (1 << check[i][prev]))))
            //     continue;

            if (!(visited & (1 << i)) && (check[i][prev] == 0 || (visited & (1 << check[i][prev]))))   // checking set bit only this way
                ans += DFS(visited, i, keys - 1);
            // if(map.find(prev) != map.end() && check(i, prev, visited))
            //     continue;
        }

        visited &= ~(1 << prev);
        return ans;
    }

    int numberOfPatterns(int l, int r) {
        cnt = 0, m = l, n = r;
        long visited = 0;

        check.resize(10, vector<int>(10, 0));

        check[1][7] = check[7][1] = 4;
        check[1][3] = check[3][1] = 2;
        check[1][9] = check[9][1] = check[3][7] = check[7][3] = check[2][8] = check[8][2] = check[4][6] = check[6][4] = 5;
        check[9][7] = check[7][9] = 8;
        check[9][3] = check[3][9] = 6;

        // map.insert({1,{47,23,59}});
        // map.insert({2,{58}});
        // map.insert({8,{52}});
        // map.insert({3,{21,69,57}});
        // map.insert({6,{54}});
        // map.insert({4,{56}});
        // map.insert({7,{41,53,89}});
        // map.insert({9,{51,87,63}});

        for (int i = m; i <= n; i++) {
            cnt += 4 * DFS(visited, 1, i - 1);
            cnt += 4 * DFS(visited, 2, i - 1);
            cnt += DFS(visited, 5, i - 1);
        }

        return cnt;
    }
};