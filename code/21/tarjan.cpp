#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
#define LL long long
#define BLACK true

struct edge { int c, u, v; };
bool operator < (const edge &a, const edge &b) {
    return a.c > b.c;
}

struct dsu {
    int *cha, *rank;
    dsu(int n): cha(new int[n+1]) {
        for (int i=0; i<=n; i++) cha[i] = i;
    }
    int find(int u) {
        if (cha[u] != u) cha[u] = find(cha[u]);
        return cha[u];
    }
    void join(int u, int v) {
        if (rand()&1) swap(u, v);
        cha[find(u)] = find(v);
    }
};

namespace lca {
    LL res = 0;
    int n, cha[100001], c[100001];
    bool color[100001];
    vector<int> queries[100001];
    struct pack { int c, v; };
    vector<pack> ke[100001];
    struct queue_type { int u, v; };
    vector<queue_type> queue[100001];
    int find(int u) {
        if (cha[u] != u) {
            int tmp = cha[u];
            cha[u] = find(cha[u]);
            c[u] = min(c[u], c[tmp]);
        }
        return cha[u];
    }
    void dfs(int u, int dad) {
        cha[u] = u;
        for (pack p: ke[u]) if (p.v != dad) {
            dfs(p.v, u);
            cha[p.v] = u;
            c[p.v] = p.c;
        }
        color[u] = BLACK;
        for (int v: queries[u]) if (color[v] == BLACK) {
            queue[find(v)].push_back({u, v});
        }
        for (auto q: queue[u]) {
            find(q.u), find(q.v);
            res += min(c[q.u], c[q.v]);
        }
    }
    void solve() {
        for (int i=1; i<=n; i++) c[i] = 10000000;
        dfs(1, 0);
    }
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    int n, m; cin >> n >> m;
    vector<edge> edges(m);
    for (edge &e: edges) cin >> e.u >> e.v >> e.c;
    sort(edges.begin(), edges.end());
    dsu d(n);
    LL res = 0;
    for (edge &e: edges) {
        if (d.find(e.u) != d.find(e.v)) {
            d.join(e.u, e.v);
            lca::ke[e.u].push_back({e.c, e.v});
            lca::ke[e.v].push_back({e.c, e.u});
        } else {
            res += e.c;
            lca::queries[e.u].push_back(e.v);
            lca::queries[e.v].push_back(e.u);
        }
    }
    lca::n = n;
    lca::solve();
    cout << lca::res - res;
    return 0;
}
