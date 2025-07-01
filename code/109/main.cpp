#include <iostream>
using namespace std;

int c[301][301];
int d[301];
bool b[301];

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    int n; cin >> n;
    for (int i=1; i<=n; i++) {
        int x; cin >> x;
        c[i][0] = c[0][i] = x;
    }
    for (int i=1; i<=n; i++) for (int j=1; j<=n; j++) {
        cin >> c[i][j];
    }

    for (int i=1; i<=n; i++) d[i] = 1e9;
    for (int z=n; z--;) {
        int u = -1;
        for (int i=0; i<=n; i++) if (!b[i]) {
            if (u<0 || d[u] > d[i]) u = i;
        }
        if (u < 0) break;
        b[u] = true;
        for (int i=0; i<=n; i++) if (!b[i]) {
            d[i] = min(d[i], c[i][u]);
        }
    }

    int res = 0;
    for (int i=1; i<=n; i++) res += d[i];
    cout << res;
    return 0;
}
