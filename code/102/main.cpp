#include <iostream>
#include <vector>
using namespace std;

struct pack { int u, c; };
typedef vector<vector<pack>> dsk;

int d[1001], bac[1001], cha[1001];

void dfs(int u, const dsk &ke) {
    for (pack p: ke[u]) if (p.u != cha[u]) {
        int v = p.u, c = p.c;
        d[v] = c;
        cha[v] = u;
        bac[v] = bac[u] + 1;
        dfs(v, ke);
    }
}

int solve(int u, int v) {
#define up(u) sum += d[u], u = cha[u]
    int sum = 0;
    while (bac[u] > bac[v]) up(u);
    while (bac[v] > bac[u]) up(v);
    while (u != v) up(u), up(v);
    return sum;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    int n, q; cin >> n >> q;
    dsk ke(n+1);
    for (int i=1; i<n; i++) {
        int u, v, c;
        cin >> u >> v >> c;
        ke[u].push_back({v, c});
        ke[v].push_back({u, c});
    }
    dfs(1, ke);
    while (q--) {
        int u, v; cin >> u >> v;
        cout << solve(u, v) << '\n';
    }
    return 0;
}
