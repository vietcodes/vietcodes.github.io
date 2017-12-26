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
    int min_index = n;
    for (int i=0, j=-1; i<=n; i++) {
        while (j<n && s[i].first-s[j+1].first >= p) {
            min_index = min(min_index, s[++j].second);
        }
        if (j>=0) {
            res = max(res, s[i].second - min_index);
        }
    }

    if (res == 0) res = -1;
    cout << res;
    return 0;
}
