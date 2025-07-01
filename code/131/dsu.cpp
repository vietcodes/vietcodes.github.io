#include <vector>
#include <iostream>
#include <cstdlib>
using namespace std;

struct dsu {
    vector<int> cha, rank, n, m;
    dsu(int N): cha(N+1), n(N+1), m(N+1) {
        for (int i=1; i<=N; i++) {
            cha[i] = i;
            m[i] = 0;
            n[i] = 1;
        }
    }
    int find(int u) {
        if (cha[u] != u) cha[u] = find(cha[u]);
        return cha[u];
    }
    void join(int u, int v) {
        u = find(u), v = find(v);
        if (u == v) {
            m[u]++;
            return;
        }
        if (rand()&1) swap(u, v);
        cha[v] = u;
        n[u] += n[v];
        m[u] += m[v] + 1;
    }
};

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    int n, m; cin >> n >> m; 
    dsu d(n);
    while (m--) {
        int u, v; cin >> u >> v;
        d.join(u, v);
    }
    int res = 0;
    for (int i=1; i<=n; i++) if (d.cha[i] == i) res += d.m[i] - d.n[i] + 1;
    cout << res;
    return 0;
}
