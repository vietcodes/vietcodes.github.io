#include <iostream>
#include <vector>
using namespace std;

vector<vector<int>> array(int n) {
    return vector<vector<int>>(n+1, vector<int>(n+1, 0));
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
            d[i][j] = d[i][j-1] + x;
            c[i][j] = c[i-1][j] + x;
            if (~d[i][j] & 1) f[i][j] |= ~f[i-1][j];
            if (~c[i][j] & 1) f[i][j] |= ~f[i][j-1];
        }
        cout << (f[n][n]? "YES\n":"NO\n");
    }
}
