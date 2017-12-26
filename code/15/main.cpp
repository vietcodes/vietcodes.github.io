#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>
using namespace std;

struct Fenwick {
    int n;
    vector<int> f;
    Fenwick(int n): n(n), f(n+1, 0) {}
    void set(int x, int i) {
        for (; i<=n; i += i&(-i)) f[i] ^= x;
    }
    int get(int i) const {
        int r = 0;
        for (; i>=1; i -= i&(-i)) r ^= f[i];
        return r;
    }
    int get(int l, int r) const {
        return get(r) ^ get(l);
    }
};

typedef vector<vector<int>> dsk;

int prepare(int u, vector<int> &nChild, dsk &ke, vector<int> &cha, vector<int> &bac) {
    nChild[u] = 1;
    for (int i=0; i<(int)ke[u].size(); i++) if (nChild[ke[u][i]]) {
        ke[u][i] = ke[u].back();
        ke[u].pop_back();
        break;
    }
    for (auto v: ke[u]) {
        cha[v] = u;
        bac[v] = bac[u] + 1;
        nChild[u] += prepare(v, nChild, ke, cha, bac);
    }
    return nChild[u];
}

void hld(int u,
        int &nChain,
        int &count,
        vector<int> &chainHead,
        vector<int> &chain,
        vector<int> &pos,
        const dsk &dscon,
        const vector<int> &nChild)
{
    if (!chainHead[nChain]) chainHead[nChain] = u;
    chain[u] = nChain;
    pos[u] = ++count;
    int con = 0;
    for (auto v: dscon[u]) if (!con || nChild[con] < nChild[v]) con = v;
    if (con) hld(con, nChain, count, chainHead, chain, pos, dscon, nChild);
    for (auto v: dscon[u]) if (v != con) {
        nChain++;
        chainHead.push_back(0);
        hld(v, nChain, count, chainHead, chain, pos, dscon, nChild);
    }
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    int T; cin >> T;
    while (T--) {
        struct edge {int i, u, v, c; };
        int n; cin >> n;
        vector<edge> edges(n-1);
        for (auto &e: edges) cin >> e.u >> e.v >> e.c;
        sort(edges.begin(), edges.end(), [](edge &a, edge &b){return a.c < b.c;});
        vector<int> cha(n + 1, 0), nChild(n+1, 0), bac(n+1, 0);
        dsk ke(n + 1);
        for (auto &e: edges) {
            ke[e.u].push_back(e.v);
            ke[e.v].push_back(e.u);
        }
        prepare(1, nChild, ke, cha, bac);
        int nChain = 0, count = 0;
        vector<int> chainHead(1, 0), chain(n + 1), pos(n + 1);
        hld(1, nChain, count, chainHead, chain, pos, ke, nChild);
        int m; cin >> m;
        vector<edge> queries(m);
        for (int i=0; i<m; i++) {
            queries[i].i = i;
            cin >> queries[i].u >> queries[i].v >> queries[i].c;
        }
        sort(queries.begin(), queries.end(), [](edge &a, edge &b){return a.c < b.c;});
        Fenwick f(n);
        vector<int> w(n+1, 0);
        auto it = edges.begin();
        for (auto &q: queries) {
            while (it != edges.end() && it->c <= q.c) {
                if (chain[it->u] != chain[it->v]) {
                    if (cha[it->u] == it->v) w[it->u] = it->c;
                    else w[it->v] = it->c;
                } else {
                    if (cha[it->u] == it->v) f.set(it->c, pos[it->u]);
                    else f.set(it->c, pos[it->v]);
                }
                it++;
            }
            int u = q.u, v = q.v;
            int res = 0;
            while (chain[u] != chain[v]) {
                int hu = chainHead[chain[u]], hv = chainHead[chain[v]];
                if (bac[hu] > bac[hv]) swap(u, v), swap(hu, hv);
                res ^= f.get(pos[v], pos[hv]);
                res ^= w[hv];
                v = cha[hv];
            }
            res ^= f.get(pos[u], pos[v]);
            q.c = res;
        }
        sort(queries.begin(), queries.end(), [](edge &a, edge &b){return a.i<b.i;});
        for (auto &q: queries) cout << q.c << '\n';
    }
    return 0;
}
