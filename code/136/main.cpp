#include <iostream>
#include <vector>
using namespace std;

const int inf = 1000000000;

struct dijkstra {
    struct edge {int v, c; };
    int n;
    vector<vector<edge>> ke;
    dijkstra(int n): n(n), ke(n+1) {}
    void add_edge(int u, int v, int c) {
        ke[u].push_back({v, c});
    }
    vector<int> run(int s) const {
        vector<int> d(n+1, inf);
        vector<bool> fixed(n+1, false);
        d[s] = 0;
        while (true) {
            int u = 0;
            for (int i=1; i<=n; i++) if (!fixed[i]) {
                if (!u || d[u] > d[i]) u = i;
            }
            if (!u) break;
            fixed[u] = true;
            for (edge e: ke[u]) if (d[e.v] > d[u] + e.c) {
                d[e.v] = d[u] + e.c;
            }
        }
        return d;
    }
};

struct graph {
    struct edge { int v, l, t; };
    int n, k;
    vector<vector<edge>> ke;
    vector<int> dl, dt;
    vector<bool> visited;
    int res;
    graph(int n, int k): n(n), k(k), ke(n+1) {}
    void add_edge(int u, int v, int l, int t) {
        ke[u].push_back({v, l, t});
    }
    void visit(int u, int l, int t) {
        if (t + dt[u] > k) return;
        if (l + dl[u] >= res) return;
        if (u == n) {
            res = min(res, l);
            return;
        }
        visited[u] = true;
        for (edge e: ke[u]) if (!visited[e.v]) {
            visit(e.v, l + e.l, t + e.t);
        }
        visited[u] = false;
    }
    int solve() {
        dijkstra gl(n), gt(n);
        for (int u=1; u<=n; u++) {
            for (edge e: ke[u]) {
                gl.add_edge(e.v, u, e.l);
                gt.add_edge(e.v, u, e.t);
            }
        }
        dl = gl.run(n);
        dt = gt.run(n);
        visited.resize(n+1, false);
        res = inf;
        visit(1, 0, 0);
        return res==inf? -1:res;
    }
};

void solve() {
    int k, n, m; cin >> k >> n >> m;
    graph g(n, k);
    while (m--) {
        int u, v, l, t;
        cin >> u >> v >> l >> t;
        g.add_edge(u, v, l, t);
    }
    cout << g.solve() << '\n';
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    int T; cin >> T;
    while (T--) solve();
    return 0;
}
