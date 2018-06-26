#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>
using namespace std;

vector<int> longest_increasing_subsequence(vector<int> a) {
    vector<int> b(a.size()+1, INT_MAX);
    b[0] = INT_MIN;
    for (int &x: a) {
        int k = lower_bound(b.begin(), b.end(), x) - b.begin();
        b[k] = x;
        x = k;
    }
    return a;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    int n; cin >> n;
    vector<int> a(n);
    for (int &x: a) cin >> x;
    reverse(a.begin(), a.end());
    auto f = longest_increasing_subsequence(a);
    for (int &x: a) x = -x;
    auto g = longest_increasing_subsequence(a);
    int res = 0;
    for (int i=0; i<n; i++) res = max(res, f[i] + g[i] - 1);
    cout << res;
    return 0;
}
