#include <iostream>
#include <vector>
#include <climits>
#include <queue>
#include <tuple>
using namespace std;

typedef long long ll;
typedef pair<int, int> pii;
typedef vector<vector<pii>> dsk;
typedef priority_queue<pii, vector<pii>, greater<pii>> min_heap;

pair<vector<int>, vector<ll>> dijkstra(int s, const dsk &ke) {
    vector<int> f(ke.size(), INT_MAX);
    vector<ll> g(ke.size(), 0);
    min_heap heap;

    f[s] = 0;
    g[s] = 1;
    heap.push({f[s], s});
    while (!heap.empty()) {
        while (!heap.empty() && heap.top().first > f[heap.top().second]) {
            heap.pop();
        }
        if (heap.empty()) break;

        int u = heap.top().second;
        heap.pop();
        for (auto &p: ke[u]) {
            int c, v;
            tie(c, v) = p;

            if (f[u]+c < f[v]) {
                g[v] = g[u];
                f[v] = f[u] + c;
                heap.push({f[v], v});
            } else if (f[u]+c == f[v]) {
                g[v] += g[u];
            }
        }
    }

    return {f, g};
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    
    int n, m; cin >> n >> m;
    dsk ke(n+1);
    while (m--) {
        int u, v, c;
        cin >> u >> v >> c;
        ke[u].push_back({c, v});
        ke[v].push_back({c, u});
    }

    vector<int> f1, fn;
    vector<ll> g1, gn;
    tie(f1, g1) = dijkstra(1, ke);
    tie(fn, gn) = dijkstra(n, ke);

    vector<int> res;
    for (int i=2; i<n; i++) {
        if (f1[i]+fn[i] > f1[n] || g1[i]*gn[i] < g1[n]) res.push_back(i);
    }

    cout << res.size() << '\n';
    for (int x: res) cout << x << '\n';
    return 0;
}
