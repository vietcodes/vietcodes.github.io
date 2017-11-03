#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

typedef vector<vector<int>> dsk;

#define N 30001
bool visited[N];
int active[N];
vector<int> stack;

int root[N];
int find(int u) {
    if (root[u] != u) root[u] = find(root[u]);
    return root[u];
}

void dfs(int u, const dsk &ke) {
    visited[u] = true;
    root[u] = u;
    stack.push_back(u);

    for (int v: ke[u]) if (visited[v]) {
        v = find(active[v]);
        while (stack.back() != v) {
            root[find(stack.back())] = v;
            stack.pop_back();
        }
    }

    for (int v: ke[u]) if (!visited[v]) {
        active[u] = v;
        dfs(v, ke);
    }

    if (stack.back() == u) stack.pop_back();
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    int n, m; cin >> n >> m;
    if (m == 0) {
        cout << 1;
        return 0;
    }
    dsk ke(n+1);
    while (m--) {
        int u, v; cin >> u >> v;
        ke[u].push_back(v);
        ke[v].push_back(u);
    }

    for (int i=1; i<=n; i++) if (!visited[i]) dfs(i, ke);

    vector<int> count(n+1, 0);
    for (int i=1; i<=n; i++) count[find(i)]++;

    cout << 1 + *max_element(count.begin(), count.end());
    return 0;
}
