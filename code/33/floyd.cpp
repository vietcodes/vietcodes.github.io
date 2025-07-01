#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    int T; cin >> T;
    while (T--) {
        int n, m; cin >> n >> m;
        vector<vector<int>> a(n, vector<int>(n, 1e9));
#define rep(i, a, b) for (int i=a; i<b; i++)
        rep(i, 0, n) a[i][i] = 0;
        while (m--) {
            int u, v, c;
            cin >> u >> v >> c;
            a[u - 1][v - 1] = c;
        }
        rep(k, 0, n) rep(i, 0, n) rep(j, 0, n) {
            if (a[i][j] > a[i][k] + a[k][j]) {
                a[i][j] = a[i][k] + a[k][j];
            }
        }
        rep(i, 0, n) {
            rep(j, 0, n) if (a[i][j] == 1e9) {
                a[i][j] = 0;
            }
        }
        rep(i, 0, n) {
            int res = -1;
            rep(j, 0, n) if (a[i][j] && a[j][i]) {
                if (res < 0) res = a[i][j] + a[j][i];
                else res = min(a[i][j] + a[j][i], res);
            }
            cout << res << '\n';
        }
    }
    return 0;
}
