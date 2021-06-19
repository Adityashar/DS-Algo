#include<bits/stdc++.h>
using namespace std;

#define pp pair<int, int>
#define f first
#define s second

vector<int> p;

int find(int x) {
    if (p[x] != x) p[x] = find(p[x]);
    return p[x];
}

bool un(int x, int y) {
    int xp = find(x), yp = find(y);
    if (xp == yp)
        return false;

    p[yp] = xp;
    return true;
}


int main() {

    int n, m;
    cin >> n >> m;

    for (int i = 0; i < n; i++)
        p.push_back(i);

    vector<pp> edges;

    for (int i = 0; i < m; i++) {
        int x, y;
        cin >> x >> y;
        edges.push_back({x - 1, y - 1});
        un(x - 1, y - 1);
    }

    int q; cin >> q;

    while (q--) {
        int x, y;
        cin >> x >> y;
        int xp = find(x - 1), yp = find(y - 1);

        if (xp == yp)
            cout << "YES" << endl;
        else
            cout << "NO" << endl;
    }

    return 0;
}