#include <iostream>
#include <vector>
using namespace std;
#define ll long long

int main() {
    ios::sync_with_stdio(false); cin.tie(0);

    int n; cin >> n;
    vector<ll> x(n + 1), y(n + 1), f(n + 1, 1ll << 50);

    for (int i=1; i <= n; i++) cin >> x[i] >> y[i];

    f[0] = 0;
    for (int i=1; i <= n; i++) {
        for (int j = i / 2; j >= 1; j--) {
            f[j] = min(f[j] + y[i], f[j-1] + x[i]);
        }
        f[0] += y[i];
    }
    cout << f[n / 2];
}
