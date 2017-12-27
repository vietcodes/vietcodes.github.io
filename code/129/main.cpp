#include <iostream>
#include <vector>
using namespace std;

struct value {
    int min, max;
    value(): min(10000000), max(0) {}
    void update(const value &v) {
        if (min > v.min) min = v.min;
        if (max < v.max) max = v.max;
    }
};

struct Tarjan {
    struct Edge { int v, c; };
    struct Query { int v, id; };
    struct Queue {int u, v, id; };
    int n, k;
    vector<vector<Edge>> ke;
    vector<vector<Query>> q;
    vector<vector<Queue>> queue;
    vector<int> cha;
    vector<bool> done;
    vector<value> c, res;

    Tarjan(int n): n(n), k(0), ke(n+1), q(n+1), queue(n+1), cha(n+1), done(n+1, false), c(n+1)  {}
    void add_edge(int u, int v, int c) {
        ke[u].push_back({v, c});
        ke[v].push_back({u, c});
    }
    void add_query(int u, int v) {
        q[u].push_back({v, k});
        q[v].push_back({u, k});
        k++;
    }
    void solve() {
        res.resize(k);
        dfs(1, 0);
    }
    int find(int u) {
        if (cha[u] != u) {
            int tmp = cha[u];
            cha[u] = find(cha[u]);
            c[u].update(c[tmp]);
        }
        return cha[u];
    }
    void dfs(int u, int dad) {
        cha[u] = u;
        for (auto e: ke[u]) if (e.v != dad) {
            dfs(e.v, u);
            cha[e.v] = u;
            c[e.v].min = c[e.v].max = e.c;
        }
        done[u] = true;
        for (auto p: q[u]) if (done[p.v]) {
            queue[find(p.v)].push_back({u, p.v, p.id});
        }
        for (auto q: queue[u]) {
            find(q.u), find(q.v);
            value tmp = c[q.u];
            tmp.update(c[q.v]);
            res[q.id] = tmp;
        }
    }
};

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    int n; cin >> n;
    Tarjan t(n);
    for (int i=1; i<n; i++) {
        int u, v, c; cin >> u >> v >> c;
        t.add_edge(u, v, c);
    }
    int k; cin >> k;
    while (k--) {
        int u, v; cin >> u >> v;
        t.add_query(u, v);
    }
    t.solve();
    for (auto v: t.res) cout << v.min << ' ' << v.max << '\n';
    return 0;
}
