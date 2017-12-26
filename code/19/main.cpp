#include <iostream>
#include <vector>
using namespace std;

vector<vector<int>> array(int n) {
    return vector<vector<int>>(2, vector<int>(n+1, 0));
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    int T; cin >> T;
    while (T--) {
        int n; cin >> n;
        auto f = array(n), c = array(n), d = array(n);
#define rep(i,a,b) for(int i=a; i<=b; i++)
        rep(i, 1, n) rep(j, 1, n) {
            int x; cin >> x;
            d[i&1][j] = d[i&1][j-1] ^ x;
            c[i&1][j] = c[~i&1][j] ^ x;
            f[i&1][j] = 0;
            if (~d[i&1][j] & 1) f[i&1][j] |= ~f[~i&1][j];
            if (~c[i&1][j] & 1) f[i&1][j] |= ~f[i&1][j-1];
        }
        cout << (f[n&1][n]? "YES\n":"NO\n");
    }
}
