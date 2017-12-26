#include <iostream>
#include <vector>
#include <cstdlib>
using namespace std;

struct dsu {
    vector<int> cha;
    dsu(int n): cha(n+1) {
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

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    int n, m; cin >> n >> m;
    dsu f(n);
    for (int i=2; i<=n; i++) {
        int x, k;
        cin >> x >> k;
        if (k==1) f.join(i, x);
    }
    while (m--) {
        int u, v;
        cin >> u >> v;
        cout << (f.find(u) != f.find(v)? "YES":"NO") << '\n';
    }
    return 0;
}
