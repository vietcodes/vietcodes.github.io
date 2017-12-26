#include <iostream>
#include <vector>
#include <numeric>
using namespace std;

#define LL long long

struct Node {
    int low = 0, index = 0;
    int trace = -1;
    LL n_child = 0;
    bool visited = false;
    vector<int> ke;
};

typedef vector<Node> Graph;

void count_child(int u, Graph &g) {
    g[u].visited = true;
    g[u].n_child = 1;
    for (int v: g[u].ke) if (!g[v].visited) {
        count_child(v, g);
        g[u].n_child += g[v].n_child;
    }
}

void dfs(int u, LL size, int &index, LL &count, Graph &g) {
    index += 1;
    g[u].index = g[u].low = index;
    vector<LL> c;

    for (int v: g[u].ke) {
        if (!g[v].index) {
            g[v].trace = u;
            dfs(v, size, index, count, g);
            if (g[v].low >= g[u].index) {
                c.push_back(g[v].n_child);
            }
            g[u].low = min(g[u].low, g[v].low);
        } else if (v != g[u].trace) {
            g[u].low = min(g[u].low, g[v].index);
        }
    }

    if (!c.empty()) {
        c.push_back(size - 1 - accumulate(c.begin(), c.end(), 0));
        count += (size - 1) * (size - 1);
        for (LL c: c) count -= c*c;
    }
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);

    int n, m; cin >> n >> m;
    Graph g(n);
    while (m--) {
        int u, v; cin >> u >> v;
        u -= 1, v -= 1;
        g[u].ke.push_back(v);
        g[v].ke.push_back(u);
    }
    
    int index(0);
    LL count(0);
    for (int i=0; i<n; i++) if (!g[i].visited) {
        count_child(i, g);
        dfs(i, g[i].n_child, index, count, g);
    }

    double result = double(count / 2) / double(n);
    printf("%.2lf", result);
    return 0;

}
