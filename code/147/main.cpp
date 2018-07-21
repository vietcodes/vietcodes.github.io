#include <iostream>
using namespace std;
#define H 500001
int f[H], g[H];

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    int n, h;
    cin >> n >> h;
    for (int i=0; i<n; i++) {
        int x; cin >> x;
        if (i & 1) f[x]++;
        else g[x]++;
    }
    for (int i=h-1; i>=0; i--) {
        f[i] += f[i + 1];
        g[i] += g[i + 1];
    }
    int res = n + 1, count = 0;
    for (int i=1; i<=h; i++) {
        int c = f[i] + g[h - i + 1];
        if (res == c) count++;
        else if (res > c) {
            res = c;
            count = 1;
        }
    }
    cout << res << ' ' << count;
    return 0;
}
