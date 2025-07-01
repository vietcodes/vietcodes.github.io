#include <iostream>
#include <vector>
#include <queue>
using namespace std;

struct matcher {
    const int oo = 100000000;
    int m, n;
    vector<int> mx, my, dist;
    vector<vector<int>> ke;
    int matched;

    matcher(int m, int n):
        m(m), n(n),
        mx(m+1, 0), my(n+1, 0), dist(m+1),
        ke(m+1),
        matched(0) {}

    void add_edge(int u, int v) {
        ke[u].push_back(v);
    }

    bool bfs() {
        queue<int> Q;
        for (int u=1; u<=m; u++) {
            if (!mx[u]) {
                dist[u] = 0;
                Q.push(u);
            } else {
                dist[u] = oo;
            }
        }

        bool found = false;
        while (!Q.empty()) {
            int u = Q.front(); Q.pop();
            for (int v: ke[u]) {
                if (!my[v]) {
                    found = true;
                } else if (dist[my[v]] == oo) {
                    dist[my[v]] = dist[u] + 1;
                    Q.push(my[v]);
                }
            }
        }

        return found;
    }

    bool dfs(int u) {
        if (dist[u] == oo) return false;
        for (int v: ke[u]) {
            if (!my[v] || (dist[my[v]]==dist[u]+1 && dfs(my[v]))) {
                mx[u] = v;
                my[v] = u;
                return true;
            }
        }
        return false;
    }

    void match() {
        while(bfs()) {
            for (int u=1; u<=m; u++) if (!mx[u]) matched += dfs(u);
        }
    }
};

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    int m, n; cin >> m >> n;
    matcher z(m, n);
    for (int u, v; cin >> u >> v;) z.add_edge(u, v);
    z.match();
    cout << z.matched << '\n';
    for (int u=1; u<=z.m; u++) if (z.mx[u]) cout << u << ' ' << z.mx[u] << '\n';
    return 0;
}
