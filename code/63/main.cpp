#include <iostream>
#include <vector>
using namespace std;
#define N 100001

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    int m, n, p;
    cin >> m >> n >> p;
    vector<bool> a(N, false), b(N, false);
    vector<int> c(p);
    while (m--) {
        int x; cin >> x;
        a[x] = true;
    }
    while (n--) {
        int x; cin >> x;
        b[x] = true;
    }
    for (int &c: c) cin >> c;

    int count_a = 0;
    for (bool x: a) if (x) count_a += 1;

    int test = 1, len = 0, count = 0;
    int res = 0;
    vector<int> f(N, 0);

    for (int x: c) {
        if (b[x]) {
            test += 1;
            len = 0;
            count = 0;
        } else {
            len += 1;
            if (a[x] && f[x] != test) {
                f[x] = test;
                count += 1;
            }
            if (count == count_a) res = max(res, len);
        }
    }

    cout << res;
    return 0;
}
