#include <iostream>
#include <vector>
using namespace std;

#define LL long long

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

struct pack { int u, v; };

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    int T; cin >> T;
    while (T--) {
        int n, m, Q; cin >> n >> m >> Q;
        vector<pack> e(m);
        vector<int> w(m);
        for (int i=0; i<m; i++) cin >> e[i].u >> e[i].v >> w[i];
        while (Q--) {
            int id; cin >> id; id--;
            int s; cin >> s;
            vector<int> ww(w);
            while (s--) {
                int t, w; cin >> t >> w;
                ww[t-1] = w;
            }
            universe a(n);
            for (int i=0; i<m; i++) if (ww[i] < ww[id]) {
                a.join(e[i].u, e[i].v);
            }
            if (a.join(e[id].u, e[id].v)) cout << "NO\n";
            else cout << "YES\n";
        }
    }
    return 0;
}
