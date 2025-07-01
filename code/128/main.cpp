#include <vector>
#include <iostream>
using namespace std;

typedef vector<vector<int>> dsk;

int cha[800];
int find(int u) {
    if (cha[u] != u) cha[u] = find(cha[u]);
    return cha[u];
}

vector<int> stack;
bool visited[800], instack[800];

void dfs(int u, dsk &ke) {
    visited[u] = true;
    instack[u] = true;
    stack.push_back(u);
    for (int v: ke[u]) if (instack[v]) {
        v = find(v);
        while (stack.back() != v) {
            cha[stack.back()] = v;
            stack.pop_back();
        }
    }
    for (int v: ke[u]) if (!visited[v]) dfs(v, ke);
    instack[u] = false;
    if (stack.back() == u) stack.pop_back();
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    int n, m; cin >> n >> m;
    dsk ke(n);
    while (m--) {
        int u, v; cin >> u >> v;
        ke[u-1].push_back(v-1);
    }
    for (int i=0; i<n; i++) cha[i] = i;
    for (int i=0; i<n; i++) if (!visited[i]) dfs(i, ke);

    vector<int> f(n, 0);
    for (int i=0; i<n; i++) f[i] = (cha[i] == i);
    for (int i=0; i<n; i++) {
        for (int j: ke[i]) {
            if (find(i) != find(j)) f[find(j)] = 0;
        }
    }
    int res = 0;
    for (int i=0; i<n; i++) res += f[i];
    cout << res;
    return 0;
}
