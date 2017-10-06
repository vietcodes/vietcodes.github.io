#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

typedef pair<int,int> pii;

int main() {
    ios::sync_with_stdio(false); cin.tie(0);

    int n, p; cin >> n >> p;
    vector<pii> s(n+1);
    s[0] = {0, 0};
    for (int i=1; i<=n; i++) {
        int a; cin >> a;
        s[i] = {s[i-1].first + a,i};
    }

    sort(s.begin(), s.end());
    int res = 0;
    for (int i=0, l=-1, f=n; i<=n; i++) {
        while (l<n && s[i].first-s[l+1].first >= p) {
            f = min(f,s[++l].second);
        }
        if (l>=0) {
            res = max(res, s[i].second - f);
        }
    }

    if (res == 0) res = -1;
    cout << res;
    return 0;
}
