#include <iostream>
#include <vector>
#include <string>
using namespace std;

void calc(int &res, int x, int y, const vector<string> &a, const vector<string> &b) {
    int m = a.size(), n = a[0].size();
    int low_i = max(0, x), high_i = min(m, m + x);
    int low_j = max(0, y), high_j = min(n, n + y);
    if ((high_i - low_i)*(high_j - low_j) <= res) return;
    vector<int> f(high_j, 0);
    vector<int> l(high_j), q(high_j), idx(high_j);
    for (int i=low_i; i < high_i; i++) {
        int top = 0;
        for (int j=low_j; j < high_j; j++) {
            if (a[i][j] == b[i-x][j-y]) {
                f[j]++;
                while (top && q[top-1]>=f[j]) top--;
                if (!top) l[j] = low_j-1;
                else l[j] = idx[top-1];
                q[top] = f[j], idx[top] = j, top++;
            } else {
                f[j] = 0;
                q[0] = 0, idx[0] = j, top = 1;
            }
        }
        top = 0;
        int r;
        for (int j=high_j-1; j >= low_j; j--) {
            if (f[j]) {
                while (top && q[top-1]>=f[j]) top--;
                if (!top) r = high_j;
                else r = idx[top-1];
                res = max(res, f[j]*(r - l[j] - 1));
                q[top] = f[j], idx[top] = j, top++;
            } else {
                q[0] = 0, idx[0] = j, top = 1;
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    int T; cin >> T;
    while (T--) {
        int n, m; cin >> m >> n;
        vector<string> a(m), b(m);
        for (auto &s: a) cin >> s;
        for (auto &s: b) cin >> s;
        int res = 0;
        for (int i=-m+1; i<m; i++) for (int j=-n+1; j<n; j++) {
            calc(res, i, j, a, b);
        }
        cout << res << '\n';
    }
    return 0;
}
