#include <vector>
#include <iostream>
#include <bitset>
using namespace std;

struct universe {
    vector<int> cha, rank;
    universe(int n): cha(n + 1), rank(n + 1, 0) {
        for (int i=1; i<=n; i++) cha[i] = i;
    }
    int find(int u) {
        if (cha[u] != u) cha[u] = find(cha[u]);
        return cha[u];
    }
    bool join(int u, int v) {
        u = find(u), v = find(v);
        if (u == v) return false;
        if (rank[u] == rank[v]) rank[u]++;
        if (rank[u] > rank[v]) cha[v] = u;
        else cha[u] = v;
        return true;
    }
    void reset() {
        for (size_t i=1; i<cha.size(); i++) cha[i] = i, rank[i] = 0;
    }
};

#define ALL(a) a.begin(), a.end()
struct edge { int u, v, id; };

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    int T; cin >> T;
    while (T--) {
        int n, m; cin >> n >> m;
        vector<int> cost_a(n, 0), cost_b(n, 0);
        for (int i=1; i<n; i++) cin >> cost_a[i];
        for (int i=1; i<n; i++) cin >> cost_b[i];
        vector<edge> a, b;
        for (int i=1; i<=m; i++) {
            int u, v, type; cin >> u >> v >> type;
            if (type==1) a.push_back({u, v, i});
            else b.push_back({u, v, i});
        }
        universe f(n);

        int max_a = 0;
        for (edge &a: a) if (f.join(a.u, a.v)) max_a++;
        f.reset();
        int max_b = 0;
        for (edge &b: b) if (f.join(b.u, b.v)) max_b++;
        int min_a = n - 1 - max_b;

        int cost = 21e8;
        int k = -1;
        for (int i=min_a; i<=max_a; i++) {
            if (cost > cost_a[i]+cost_b[n-1-i]) {
                k = i;
                cost = cost_a[i]+cost_b[n-1-i];
            }
        }

        bitset<100001> res;
        f.reset();
        for (edge &b: b) f.join(b.u, b.v);
        for (edge &a: a) res[a.id] = f.join(a.u, a.v);
        f.reset();
        for (edge &a: a) if (res[a.id]) {
            f.join(a.u, a.v);
            k--;
        }
        if (k) for (edge &a: a) if (f.join(a.u, a.v)) {
            res[a.id] = true;
            k--;
            if (k==0) break;
        }
        for (edge &b: b) res[b.id] = f.join(b.u, b.v);

        for (int i=1; i<=m; i++) if (res[i]) cout << i << ' ';
        cout << '\n';
    }
    return 0;
}
