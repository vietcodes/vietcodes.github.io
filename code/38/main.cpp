#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

struct pack { int d, t; };
bool operator < (const pack &a, const pack &b) {
    return a.d < b.d;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    int n, a, b; cin >> n >> a >> b;
    vector<pack> d(n+1);
    for (int i=1; i<=n; i++) cin >> d[i].d >> d[i].t;

    sort(d.begin(), d.end());
    vector<int> sa(n+1), sb(n+1);
    sa[0] = sb[0] = 0;
    for (int i=1; i<=n; i++) {
        sa[i] = sa[i-1] + (d[i].t == 1);
        sb[i] = sb[i-1] + (d[i].t == 2);
    }

    int res = 2e9;
    int l = 1;
    for (int i=1; i<=n; i++) {
        while (sa[i]-sa[l-1]>=a && sb[i]-sb[l-1]>=b) {
            res = min(res, d[i].d - d[l].d);
            l++;
        }
    }

    if (res == 2e9) cout << -1;
    else cout << res;
    return 0;
}
