#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    int n; cin >> n;
    vector<int> a(n), b(n);
    for (int &a: a) cin >> a;
    for (int &b: b) cin >> b;
    sort(a.begin(), a.end());
    int res = 2e9;
    for (int b: b) {
        auto i = lower_bound(a.begin(), a.end(), -b);
        if (i != a.end()) res = min(res, abs(b + *i));
        if (i != a.begin()) res = min(res, abs(b + *(i-1)));
    }
    cout << res;
    return 0;
}
