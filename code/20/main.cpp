#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    int n; cin >> n;
    vector< vector<int> > a(401, vector<int>(401, 0));
    while (n--) {
        int u, v, c; cin >> u >> v >> c;
        a[u + 200][v + 200] = 1 << (c - 1);
    }
#define rep(i, a, b) for (int i=a; i<=b; i++)
#define LL long long
    LL res = 0;
    rep(i, 0, 400) rep(j, 0, i) {
        vector<LL> f(16, 0);
        rep(k, 0, 400) if (a[i][k] && a[j][k] && a[i][k] != a[j][k]) {
            int c = a[i][k] | a[j][k];
            res += f[15 - c];
            f[c]++;
        }
    }
    cout << res;
    return 0;
}
