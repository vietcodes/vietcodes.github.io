#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Time { int start, end; };
#define val(x) ((x).end-(x).start)
bool operator < (const Time &a, const Time &b) {
    return a.end < b.end;
}

int bs(const vector<Time> &a, int l, int r, int val) {
    while (l<=r) {
        int k = (l+r) / 2;
        if (a[k].end <= val) l = k+1;
        else r = k-1;
    }
    return r;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);

    int n; cin >> n;
    vector<Time> a(n);
    for (auto &x: a) cin >> x.start >> x.end;

    sort(a.begin(), a.end());

    vector<int> f(n);
    f[0] = val(a[0]);
    for (int i=1; i<n; i++) {
        int j = bs(a, 0, i-1, a[i].start);
        f[i] = max(f[i-1], val(a[i]) + (j>=0? f[j]:0));
    }
    cout << f[n-1];
    return 0;
}
