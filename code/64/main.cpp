#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    int n, k; cin >> n >> k;
    vector<int> a(n+1);
    a[0] = 0;
    for (int i=1; i<=n; i++) cin >> a[i];

    vector<int> f(n+1, -1e9);
    f[0] = 0;
    int res = 0;

    for (int i=1; i<=n; i++) {
        for (int j=i-1; j>=0 && j>=i-k; j--) {
            f[i] = max(f[i], f[j] + a[i]);
        }
        res = max(res, f[i]);
    }

    cout << res;
    return 0;
}
