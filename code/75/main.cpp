#include <iostream>
#include <vector>
using namespace std;

struct node {
    int index = 0, lowlink = 0;
    bool on_stack = false;
    vector<int> ke;
};

typedef vector<node> graph;

void dfs(int u, int &result, int &index, vector<int> &stack, graph &g) {
    index += 1;
    g[u].lowlink = g[u].index = index;
    stack.push_back(u);
    g[u].on_stack = true;

    for (int v: g[u].ke) {
        if (!g[v].index) {
            dfs(v, result, index, stack, g);
            g[u].lowlink = min(g[u].lowlink, g[v].lowlink);
        } else if (g[v].on_stack) {
            g[u].lowlink = min(g[u].lowlink, g[v].index);
        }
    }

    if (g[u].lowlink == g[u].index) {
        result += 1;
        int v;
        do {
            v = stack.back();
            stack.pop_back();
            g[v].on_stack = false;
        } while (v != u);
    }
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);

    int n, m; cin >> n >> m;
    graph g(n);

    while (m--) {
        int u, v; cin >> u >> v;
        u -= 1, v -= 1;
        g[u].ke.push_back(v);
    }

    int index(0), result(0);
    vector<int> stack;
    for (int i=0; i<n; i++) {
        if (!g[i].index) dfs(i, result, index, stack, g);
    }

    cout << result;
    return 0;
}
