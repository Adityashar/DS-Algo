/*

447. Number of Boomerangs

You are given n points in the plane that are all distinct,
where points[i] = [xi, yi].

A boomerang is a tuple of points (i, j, k)
such that the distance between i and j equals the distance between i and k
(the order of the tuple matters).

Input: points = [[0,0],[1,0],[2,0]]
Output: 2
Explanation:

The two boomerangs are
[[1,0],[0,0],[2,0]] and [[1,0],[2,0],[0,0]].

*/


int numberOfBoomerangs(vector<vector<int>>& points) {
    int n = points.size();
    if (n <= 2)
        return 0;

    int ans = 0;

    for (int i = 0; i < n; i++) {
        unordered_map<long, int> distances;

        for (int j = 0; j < n; j++) {
            if (i == j)
                continue;

            int dx = points[i][0] - points[j][0];
            int dy = points[i][1] - points[j][1];

            long dist = dx * dx + dy * dy;

            distances[dist]++;
        }

        for (auto i : distances)
            ans += i.second * (i.second - 1);
    }

    return ans;
}