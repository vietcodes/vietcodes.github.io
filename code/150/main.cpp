#include <algorithm>
#include <cstring>
#include <iostream>
using namespace std;
 
int a[101][101];
 
#define forn(i) for (int i = 1; i <= n; i++)
 
int main() {
    ios::sync_with_stdio(false); cin.tie(0);

    int n; cin >> n;

    int s[4];
    for (int &u : s) cin >> u;

    forn(i) forn(j) a[i][j] = 1e8;
    forn(i) a[i][i] = 0;
    for (int u, v, w; cin >> u >> v >> w;) {
        a[u][v] = a[v][u] = w;
    }

    // Floyd
    forn(k) forn(i) forn(j) {
        if (a[i][j] > a[i][k] + a[k][j]) a[i][j] = a[i][k] + a[k][j];
    }

    // Create all permutation of `s` and put them in `permute`
    sort(s, s + 4);
    int permute[96];
    for (int i = 0; i < 24; i++) {
        next_permutation(s, s + 4);
        memcpy(permute + 4 * i, s, 16);
    }

    int res = 1e8;
    forn(u) forn(v) {
        for (int i = 0; i < 24; i++) {
            int x = a[u][v];
            x += a[u][permute[0 + 4 * i]];
            x += a[u][permute[1 + 4 * i]];
            x += a[v][permute[2 + 4 * i]];
            x += a[v][permute[3 + 4 * i]];
            res = min(res, x);
        }
    }
    cout << res << endl;
}
