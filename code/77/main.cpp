#include <iostream>
#include <vector>
using namespace std;

struct Node {
    int index = 0;
    int low = 0;
    int trace = -1;
    vector<int> ke;
};

typedef vector<Node> Graph;

int index = 0;
int count_cut = 0;
int count_bridge = 0;

void dfs(int u, Graph &g) {
    index += 1;
    g[u].low = g[u].index = index;
    bool maybe_cut_vertex = false;
    int count_child = 0;

    for (int v: g[u].ke) {
        if (!g[v].index) {
            count_child += 1;
            g[v].trace = u;
            dfs(v, g);
            if (g[v].low > g[u].index) count_bridge += 1;
            if (g[v].low >= g[u].index) maybe_cut_vertex = true;
            g[u].low = min(g[u].low, g[v].low);
        } else if (v != g[u].trace) {
            g[u].low = min(g[u].low, g[v].index);
        }
    }

    if (g[u].trace == -1) {
        if (count_child > 1) count_cut += 1;
    } else if (maybe_cut_vertex) {
        count_cut += 1;
    }
}

int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    Graph g(n);
    while (m--) {
        int u, v;
        scanf("%d%d", &u, &v);
        u -= 1, v-= 1;
        g[u].ke.push_back(v);
        g[v].ke.push_back(u);
    }

    for (int i=0; i<n; i++) if (!g[i].index) {
        dfs(i, g);
    }

    printf("%d %d", count_cut, count_bridge);
    return 0;
}
