#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct universe {
    vector<int> cha, rank;
    universe(int n): cha(n + 1), rank(n + 1, 0) {
        for (int i=1; i<=n; i++) cha[i] = i;
    }
    int find(int u) {
        if (cha[u] != u) cha[u] = find(cha[u]);
        return cha[u];
    }
    bool join(int u, int v) {
        u = find(u), v = find(v);
        if (u == v) return false;
        if (rank[u] == rank[v]) rank[u]++;
        if (rank[u] > rank[v]) cha[v] = u;
        else cha[u] = v;
        return true;
    }
};

struct edge { int u, v, c; };
bool operator > (edge a, edge b) {
    return a.c > b.c;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    int n, m; cin >> n >> m;
    vector<edge> e(m);
    for (edge &e: e) cin >> e.u >> e.v >> e.c;

    universe f(n);
    int res = 0;
    sort(e.begin(), e.end(), greater<edge>());
    for (edge &e: e) if (!f.join(e.u, e.v)) res += e.c;
    cout << res;
    return 0;
}
