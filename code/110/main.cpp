#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    int n; cin >> n;
    vector<int> t(n);
    for (int &x: t) cin >> x;
    vector<int> r(n-1);
    for (int &x: r) cin >> x;
    vector<int> f(n);
    f[0] = t[0];
    f[1] = min(t[0] + t[1], r[0]);
    for (int i=2; i<n; i++) f[i] = min(t[i] + f[i-1], r[i-1] + f[i-2]);
    cout << f[n-1];
    return 0;
}
