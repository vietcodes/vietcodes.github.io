#include <iostream>
#include <vector>
using namespace std;

int a[1001], b[1001], f[1001][1001];

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    int m, n; cin >> m >> n;
    for (int i=1; i<=m; i++) cin >> a[i];
    for (int i=1; i<=n; i++) cin >> b[i];
    for (int i=1; i<=m; i++) {
        for (int j=1; j<=n; j++) {
            if (a[i] == b[j]) {
                if (i == 1 || j == 1) f[i][j] = 1;
                else f[i][j] = 1 + f[i-2][j-2];
            }
            else f[i][j] = max(f[i-1][j], f[i][j-1]);
        }
    }
    cout << f[m][n];
    return 0;
}
