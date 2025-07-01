#include <iostream>
#include <vector>
using namespace std;

typedef vector<vector<int>> dsk;
bool visited[2001], instack[2001];
int dfs(int u, int cha, dsk &ke) {
    visited[u] = true;
    instack[u] = true;
    int res = 0;
    for (int v: ke[u]) if (v != cha) {
        if (instack[v]) res++;
        if (!visited[v]) res += dfs(v, u, ke);
    }
    instack[u] = false;
    return res;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    int n, m; cin >> n >> m;
    dsk ke(n+1);
    while (m--) {
        int u, v; cin >> u >> v;
        ke[u].push_back(v);
        ke[v].push_back(u);
    }
    int res = 0;
    for (int u=1; u<=n; u++) if (!visited[u]) res += dfs(u, 0, ke);
    cout << res;
    return 0;
}
