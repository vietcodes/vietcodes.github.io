#include <iostream>
#include <vector>
#include <queue>
using namespace std;

struct Edge { int u, w; };
bool operator > (const Edge &a, const Edge &b) {
    return a.w > b.w;
}
typedef vector<vector<Edge>> Graph;
typedef priority_queue<Edge, vector<Edge>, greater<Edge>> MinHeap;

int prim (const Graph &g) {
    MinHeap heap;
    heap.push({1, 0});
    int result = 0;
    vector<bool> b(g.size(), false);
    while (!heap.empty()) {
        while (!heap.empty() && b[heap.top().u]) heap.pop();
        if (heap.empty()) break;
        Edge e = heap.top(); heap.pop();
        b[e.u] = true;
        result += e.w;
        for (Edge e: g[e.u]) heap.push(e);
    }
    return result;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);

    int n, m; cin >> n >> m;

    Graph g(n+1);
    while (m--) {
        int u, v, w;
        cin >> u >> v >> w;
        g[u].push_back({v, w});
        g[v].push_back({u, w});
    }

    cout << prim(g);
    return 0;
}
