#include <iostream>
#include <vector>
using namespace std;

int n;
int a[500], t[500][500], c[500][500];

int walk(int w) {
    vector<int> d(n, 1e9), e(n, 0);
    vector<bool> b(n, true);
    d[0] = 0;
    e[0] = w;
    for (int i=0; i<n; i++) {
        int u = -1;
        for (int v=0; v<n; v++) if (b[v]) {
            if (u<0 || d[u] > d[v]) u = v;
        }
        if (u<0) break;
        if (u==n-1) return d[u];
        b[u] = false;
        for (int v=0; v<n; v++) if (t[u][v] && e[u]-c[u][v]>=0) {
            if (d[v] > d[u] + t[u][v]) {
                d[v] = d[u] + t[u][v];
                e[v] = a[v]? w : e[u]-c[u][v];
            } else if (d[v] == d[u] + t[u][v]) {
                e[v] = max(e[v], e[u]-c[u][v]);
            }
        }
    }
    return -1;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    cin >> n;
    for (int i=0; i<n; i++) cin >> a[i];
    int m; cin >> m;
    while (m--) {
        int u, v; cin >> u >> v;
        u--, v--;
        cin >> t[u][v] >> c[u][v];
        t[v][u] = t[u][v];
        c[v][u] = c[u][v];
    }
    int tmin = walk(1e9);
    int l = 0, r = 1e9;
    while (l<=r) {
        int k = (l+r) / 2;
        if (walk(k) == tmin) r = k - 1;
        else l = k + 1;
    }
    cout << l;
    return 0;
}
