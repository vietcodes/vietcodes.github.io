#include <iostream>
#include <vector>
#include <bitset>
#include <queue>
using namespace std;

struct pack { int v, c; };
bool operator > (pack a, pack b) {
    return a.c > b.c;
}
typedef vector<vector<pack>> dsk;
typedef priority_queue<pack, vector<pack>, greater<pack>> min_heap;

vector<int> dijkstra(int s, const dsk& ke) {
    static bitset<10001> b;
    min_heap heap;
    vector<int> d(ke.size(), 1e9);

    b.reset();
    d[s] = 0;
    heap.push({s, 0});
    while (true) {
        while (!heap.empty() && b[heap.top().v]) heap.pop();  
        if (heap.empty()) break;

        int u(heap.top().v);
        d[u] = heap.top().c;
        b.set(u);
        heap.pop();
        for (pack p: ke[u]) heap.push({p.v, d[u] + p.c});
    }

    return d;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    int T; cin >> T;
    while (T--) {
        int n, m, k, s, t;
        cin >> n >> m >> k >> s >> t;
        dsk ke(n+1), rev_ke(n+1);
        while (m--) {
            int u, v, c;
            cin >> u >> v >> c;
            ke[u].push_back({v, c});
            rev_ke[v].push_back({u, c});
        }

        vector<int> ds(dijkstra(s, ke));
        vector<int> dt(dijkstra(t, rev_ke));

        int res(ds[t]);
        while (k--) {
            int u, v, c;
            cin >> u >> v >> c;
            if (ds[u] != 1e9 && dt[v] != 1e9) {
                res = min(res, ds[u] + c + dt[v]);
            }
            if (ds[v] != 1e9 && dt[u]!= 1e9) {
                res = min(res, ds[v] + c + dt[u]);
            }
        }

        if (res == 1e9) res = -1;
        cout << res << '\n';
    }
    return 0;
}
