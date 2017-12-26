#include <iostream>
#include <vector>
using namespace std;

struct pack { int i, j; };

struct UnionFind {
    int m;
    vector<int> cha, rank;
    UnionFind(int m): m(m), cha(m), rank(m) {
        reset();
    }
    void add(int i, int j, int n) {
        int id = i*n + j;
        if (cha[id] >= 0) return;
        cha[id] = id;
        if (i > 0) join(id, id-n);
        if (j > 0) join(id, id-1);
        if (i < n-1) join(id, id+n);
        if (j < n-1) join(id, id+1);
    }
    void add(const vector<pack> &p, int n) {
        for (auto &p: p) add(p.i, p.j, n);
    }
    bool test(int u, int v) {
        u = find(u);
        v = find(v);
        return u==v && u>=0;
    }

    void reset() {
        cha.assign(m, -1);
        rank.assign(m, 0);
    }
    int find(int u) {
        if (cha[u] < 0) return -1;
        if (cha[u] != u) cha[u] = find(cha[u]);
        return cha[u];
    }
    void join(int u, int v) {
        u = find(u);
        v = find(v);
        if (u < 0 || v < 0 || u == v) return;
        if (rank[u] == rank[v]) rank[u]++;
        if (rank[u]<rank[v]) cha[u] = v;
        else cha[v] = u;
    }
};

int main() {
    ios::sync_with_stdio(false); cin.tie(0);

    vector<pack> a[111];
    int low_h, high_h, max_h=0;
    int n; cin >> n;
    int m = n*n;
    for (int i=0; i<n; i++) for (int j=0; j<n; j++) {
        int h; cin >> h;
        a[h].push_back({i,j});
        if (i==0 && j==0) low_h = h;
        if (i==n-1 && j==n-1) high_h = h;
        max_h = max(max_h, h);
    }
    if (low_h > high_h) swap(low_h, high_h);

    UnionFind u(m);
    for (int h=low_h; h<=high_h; h++) u.add(a[h], n);

    int res = 111;
    for (int h=low_h; h>=0; h--) {
        u.add(a[h], n);
        UnionFind f(u);
        for (int h1=high_h; h1<=max_h; h1++) {
            f.add(a[h1], n);
            if (f.test(0, m-1)) {
                res = min(res, h1-h);
                break;
            }
        }
    }

    cout << res;
    return 0;
}
