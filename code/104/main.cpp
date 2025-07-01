#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

typedef long long ll;

ll solve(int k, const vector<double> &x, const vector<double> &y) {
    vector<double> a(k);
    for (int i=0; i<k; i++) {
        double dy = y[i] - y[k];
        if (dy != 0) a[i] = (x[i] - x[k]) / dy;
        else a[i] = 1e9;
    }
    sort(a.begin(), a.end());
    ll res = 0;
    ll count = 1;
    for (int i=1; i<k; i++) {
        if (a[i] != a[i-1]) {
            res += count*(count-1) / 2;
            count = 0;
        }
        count++;
    }
    res += count*(count-1) / 2;
    return res;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    int n; cin >> n;
    vector<double> x(n), y(n);
    for (int i=0; i<n; i++) cin >> x[i] >> y[i];
    ll res = 0;
    for (int i=2; i<n; i++) res += solve(i, x, y);
    cout << res;
    return 0;
}
