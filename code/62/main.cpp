#include <iostream>
#include <vector>
using namespace std;

struct pack { int u, l; };
typedef vector< vector<pack> > dsk;

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    int n, m; cin >> n >> m;
    dsk ke(n);
    while (m--) {
        int k, u, v, l;
        cin >> k >> u >> v >> l;
        ke[u-1].push_back({v-1, l});
        if (k == 2) ke[v-1].push_back({u-1, l});
    }

    vector<int> d(n, 1e9);
    vector<long long> f(n, 0ll);
    vector<bool> b(n, true);
    d[0] = 0;
    f[0] = 1ll;
    for (int _=n; _--;) {
        int u = -1;
        for (int v=0; v<n; v++) if (b[v]) {
            if (u == -1 || d[u] > d[v]) u = v;
        }
        if (u == -1) break;
        if (u == n-1) break;
        b[u] = false;
        for (pack p: ke[u]) {
            int v = p.u, l = p.l;
            if (d[v] > d[u] + l) {
                d[v] = d[u] + l;
                f[v] = f[u];
            } else if (d[v] == d[u] + l) {
                f[v] += f[u];
            }
        }
    }
    cout << d[n-1] << ' ' << f[n-1];
    return 0;
}
