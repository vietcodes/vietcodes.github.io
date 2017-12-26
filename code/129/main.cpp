#include <vector>
#include <iostream>
using namespace std;

struct value {
    int min, max;
    value(): min(10000000), max(0) {}
    void update(const value &v) {
        if (min > v.min) min = v.min;
        if (max < v.max) max = v.max;
    }
};
struct bit {
    int n;
    vector<value> f, a;
    bit(int n): n(n), f(n+1), a(n+1) {}
    void update(int i, int v) {
        a[i].min = a[i].max = v;
        for (; i<=n; i+=i&-i) f[i].update(a[i]);
    }
    value get(int l, int r) {
        value res;
        while (l <= r) {
            int rr = r - r&-r;
            if (l <= rr) res.update(f[r]), r = rr;
            else res.update(a[r]), r--;
        }
        return res;
    }
};

struct Node {
    int chainId, level, pos, next, cha;
    Node() {
        level = pos = next = cha = 0;
    }
};
struct edge { int u, v, c; };

typedef vector<vector<int>> dsk;
struct tree {
    int n, nChain;
    dsk ke;
    vector<Node> node;
    vector<int> chainHead;
    vector<edge> edges;
    bit f;

    tree(int n): n(n), ke(n+1), node(n+1), f(n) {}
    void add_edge(int u, int v, int c) {
        edges.push_back({u, v, c});
        ke[u].push_back(v);
        ke[v].push_back(u);
    }
    int prepare(int u, int cha) {
        for (int i=0; i<(int)ke[u].size(); i++) if (ke[u][i] == cha) {
            ke[u][i] = ke[u].back();
            ke[u].pop_back();
            break;
        }
        int nChild = 1;
        int max = 0;
        for (int v: ke[u]) {
            node[v].level = node[u].level + 1;
            node[v].cha = u;
            int vChild = prepare(v, u);
            if (vChild > max) max = vChild, node[u].next = v;
            nChild += vChild;
        }
        return nChild;
    }
    void dfs(int u, int &cnt) {
        node[u].pos = ++cnt;
        node[u].chainId = nChain-1;
        if (node[u].next) dfs(node[u].next, cnt);
        for (int v: ke[u]) if (v != node[u].next) {
            nChain++;
            chainHead.push_back(v);
            dfs(v, cnt);
        }
    }
    void hld() {
        prepare(1, 0);
        nChain = 1;
        chainHead.push_back(1);
        int cnt = 0;
        dfs(1, cnt);
        for (edge e: edges) {
            if (node[e.u].cha == e.v) swap(e.u, e.v);
            f.update(node[e.v].pos, e.c);
        }
    }
    value query(int u, int v) {
        value res;
        while (node[u].chainId != node[v].chainId) {
            int headU = chainHead[node[u].chainId];
            int headV = chainHead[node[v].chainId];
            if (node[headU].level < node[headV].level) {
                swap(u, v);
                swap(headU, headV);
            }
            res.update(f.get(node[headU].pos, node[u].pos));
            u = node[headU].cha;
        }
        if (u != v) {
            if (node[u].level > node[v].level) swap(u, v);
            res.update(f.get(node[u].pos+1, node[v].pos));
        }
        return res;
    }
    value trau(int u, int v) {
        value res;
#define up(u) res.update(f.a[node[u].pos]), u = node[u].cha
        while (node[u].level > node[v].level) up(u);
        while (node[v].level > node[u].level) up(v);
        while (u != v) up(u), up(v);
        return res;
    }
};

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    int n; cin >> n;
    tree T(n);
    for (int i=1; i<n; i++) {
        int u, v, c; cin >> u >> v >> c;
        T.add_edge(u, v, c);
    }
    T.hld();
    int m; cin >> m;
    while (m--) {
        int u, v; cin >> u >> v;
        value res = T.query(u, v);
        cout << res.min << ' ' << res.max << '\n';
    }
    return 0;
}
