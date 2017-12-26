#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

bool bs(const vector<int> &a, int x, int i) {
    if (a[i] == x) {
        return (i>0 && a[i-1]==x) || (i<(int)a.size() && a[i+1]==x);
    }

    int l = 0, r = a.size()-1;
    while (l<=r) {
        int k = (l+r) / 2;
        if (a[k] == x) return true;
        if (a[k] < x) l = k + 1;
        else r = k - 1;
    }
    return false;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    int n; cin >> n;
    vector<int> a(n);
    for (int &a: a) cin >> a;
    sort(a.begin(), a.end());
    vector<int> f(n, 0);
    int res = 0;
    for (int i=0; i<n; i++) {
        for (int j=i-1; j>=0; j--) if (bs(a, a[i]-a[j], j)) {
            f[i] = max(f[i], f[j]);
        }
        f[i] += 1;
        res = max(res, f[i]);
    }
    cout << res;
    return 0;
}
