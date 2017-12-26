#include <iostream>
#include <vector>
#include <climits>
using namespace std;

#define LL long long
typedef vector< vector<LL> > array2d;

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    int T; cin >> T;
    while (T--) {
        int m, n; cin >> m >> n;
        array2d c(m+1, vector<LL>(n+1));
        for (int i=1; i<=m; i++) {
            for (int j=1; j<=n; j++) {
                cin >> c[i][j];
            }
        }
        array2d f(m+n+1, vector<LL>(m+1, LLONG_MAX));
        array2d g(m+n+1, vector<LL>(n+1, LLONG_MAX));
        f[0][0] = g[0][0] = 0;
        for (int i=1; i<=m+n; i++) {
            for (int j=1; j<=m; j++) {
                f[i][j] = f[i-1][j-1];
                if (i-j>=0 && i-j<=n) {
                    f[i][j] = min(f[i][j], g[i-1][i-j] + c[j][i-j]);
                }
            }
            for (int j=1; j<=n; j++) {
                g[i][j] = g[i-1][j-1];
                if (i-j>=0 && i-j<=m) {
                    g[i][j] = min(g[i][j], f[i-1][i-j] + c[i-j][j]);
                }
            }
        }
        cout << min(f[m+n][m], g[m+n][n]) << '\n';
    }
    return 0;
}
