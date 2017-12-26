#include <iostream>
#include <vector>
using namespace std;

struct DisjointSet {
    vector<int> cha, rank;
    DisjointSet(int n): cha(n + 1), rank(n + 1, 0) {
        for (int i=1; i<=n; i++) cha[i] = i;
    }
    int find(int u) {
        if (cha[u] != u) cha[u] = find(cha[u]);
        return cha[u];
    }
    bool join(int u, int v) {
        u = find(u);
        v = find(v);
        if (u == v) return false;
        if (rank[u] == rank[v]) rank[u]++;
        if (rank[u] > rank[v]) cha[v] = u;
        else cha[u] = v;
        return true;
    }
};

int main() {
    ios::sync_with_stdio(false); cin.tie(0);

    int q; cin >> q;
    DisjointSet set(10000);

    while (q--) {
        int t, u, v;
        cin >> u >> v >> t;
        if (t==1) set.join(u, v);
        else cout << (set.find(u)==set.find(v)) << '\n';
    }

    return 0;
}
