#include <iostream>
#include <vector>
using namespace std;

struct DisjointSet {
    vector<int> cha, rank;
    DisjointSet(int n): cha(n + 1), rank(n + 1, 0) {
        for (int i=1; i<=n; i++) cha[i] = i;
    }
    int find(int u) {
        if (cha[u] != u) cha[u] = find(cha[u]);
        return cha[u];
    }
    bool join(int u, int v) {
        u = find(u);
        v = find(v);
        if (u == v) return false;
        if (rank[u] == rank[v]) rank[u]++;
        if (rank[u] > rank[v]) cha[v] = u;
        else cha[u] = v;
        return true;
    }
};

struct pack { int a, b; string op; };

int main() {
    ios::sync_with_stdio(false); cin.tie(0);

    int T; cin >> T;
    while (T--) {
        int n, m; cin >> n >> m;
        vector<pack> a(m);
        for (auto &x: a) cin >> x.a >> x.op >> x.b;
        DisjointSet dsu(n);
        for (auto &x: a) if (x.op == "=") dsu.join(x.a, x.b);
        bool res = true;
        for (auto &x: a) if (x.op == "!=") {
            if (dsu.find(x.a) == dsu.find(x.b)) {
                res = false;
                break;
            }
        }
        cout << (res? "YES":"NO");
        cout << '\n';
    }
    return 0;
}
