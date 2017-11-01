#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct dsu {
    vector<int> cha, rank;
    dsu(int n): cha(n + 1), rank(n + 1, 0) {
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

struct Edge { int u, v, w; };
bool operator < (const Edge &a, const Edge &b) {
    return a.w < b.w;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);

    int n, m; cin >> n >> m;
    vector<Edge> e(m);
    for (Edge &e: e) cin >> e.u >> e.v >> e.w;

    sort(e.begin(), e.end());

    int result = 0;
    dsu set(n);
    for (Edge &e: e) {
        if (set.join(e.u, e.v)) result = e.w;
    }

    cout << result;
    return 0;
}
