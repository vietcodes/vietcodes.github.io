#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    int T; cin >> T;
    while (T--) {
        int m, n; cin >> m >> n;
        vector<int> a(m), b(n);
        for (int &a: a) cin >> a;
        for (int &b: b) cin >> b;
        vector<int> x(m, 0), y(n, 0);
        int res = 0;
        for (int i=0; i<m; i++) for (int j=0; j<n; j++) {
            int tmp = x[i];
            if (b[j]*2 <= a[i]) x[i] = max(x[i], y[j]);
            if (a[i] == b[j]) {
                y[j] = tmp + 1;
                res = max(res, y[j]);
            }
        }
        cout << res << '\n';
    }
    return 0;
}
