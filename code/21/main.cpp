#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

#define LL long long
struct pack{ int u, v, c; };
typedef vector<vector<int>> dsk;

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
        if (u == v) return false;
        if (rank[u] == rank[v]) rank[u]++;
        if (rank[u] > rank[v]) cha[v] = u;
        else cha[u] = v;
        return true;
    }
};

inline void minimize(int &x, int y) {
    if (x > y) x = y;
}

struct Hld {
    dsk ke;
    vector<int> nChild, cha, bac, chainHead, chain, pos;
    vector<int> f, r, w;
    int n;
    Hld(int n, dsk &&ke): ke(ke),
    nChild(n + 1, 0), cha(n + 1), bac(n + 1),
    chainHead(1, 0), chain(n + 1), pos(n + 1),
    f(n+1, 1e9), r(n+1, 1e9), w(n+1, 1e9), n(n)
    {
        prepare(1);
        int nChain = 0, count = 0;
        hld(1, nChain, count);
    }

    int prepare(int u) {
        nChild[u] = 1;
        for (int i=0; i<(int)ke[u].size(); i++) if (nChild[ke[u][i]]) {
            ke[u][i] = ke[u].back();
            ke[u].pop_back();
            break;
        }
        for (auto v: ke[u]) {
            cha[v] = u;
            bac[v] = bac[u] + 1;
            nChild[u] += prepare(v);
        }
        return nChild[u];
    }
    void hld(int u, int &nChain, int &count) {
        if (!chainHead[nChain]) chainHead[nChain] = u;
        chain[u] = nChain;
        pos[u] = ++count;
        int con = 0;
        for (auto v: ke[u]) if (!con || nChild[con] < nChild[v]) con = v;
        if (con) hld(con, nChain, count);
        for (auto v: ke[u]) if (v != con) {
            nChain++;
            chainHead.push_back(0);
            hld(v, nChain, count);
        }
    }

    void bitUp(int x, int i) {
        r[i] = x;
        while(i <= n) minimize(f[i], x), i += i & (-i);
    }
    int bitGet(int u, int v) {
        if (u > v) swap(u, v);
        u += 1;
        int res = 1e9;
        while (u <= v) {
            if (u <= (v - v & (-v))) {
                minimize(res, f[v]);
                v -= v & (-v);
            } else {
                minimize(res, r[v]);
                v -= 1;
            }
        }
        return res;
    }

    void update(int u, int v, int c) {
        if (chain[u] != chain[v]) {
            if (cha[u] == v) w[u] = c;
            else w[v] = c;
        } else {
            if (cha[u] == v) bitUp(c, pos[u]);
            else bitUp(c, pos[v]);
        } 
    }

    int query(int u, int v) {
        int res = 1e9;
        while (chain[u] != chain[v]) {
            int hu = chainHead[chain[u]], hv = chainHead[chain[v]];
            if (bac[hu] > bac[hv]) swap(u, v), swap(hu, hv);
            minimize(res, bitGet(pos[v], pos[hv]));
            minimize(res, w[hv]);
            v = cha[hv];
        }
        minimize(res, bitGet(pos[u], pos[v]));
        return res;
    }
};

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    int n, m; cin >> n >> m;
    universe s(n);
    vector<pack> edges(m);
    for (auto &e: edges) cin >> e.u >> e.v >> e.c;
    sort(edges.begin(), edges.end(), [](pack &a, pack &b){return a.c > b.c;});
    vector<pack> q, tree;
    dsk ke(n + 1);
    for (auto &e: edges) {
        if (s.join(s.find(e.u), s.find(e.v))) {
            ke[e.u].push_back(e.v);
            ke[e.v].push_back(e.u);
            tree.push_back(e);
        } else q.push_back(e);
    }
    Hld hld(n, move(ke));
    for (auto &x: tree) hld.update(x.u, x.v, x.c);
    LL res = 0;
    for (auto &q: q) res += (LL)(hld.query(q.u, q.v) - q.c);
    cout << res;
    return 0;
}
