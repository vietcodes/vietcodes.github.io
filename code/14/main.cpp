#include <iostream>
#include <algorithm>
#include <vector>
#include <memory>
using namespace std;

#define LL long long

LL pow(LL a, LL n, LL m) {
    if (n == 0) return 1;
    LL t = pow(a, n>>1, m);
    if (n & 1) return t * t % m * a % m;
    return t * t % m;
}

LL calc(LL n, LL m) {
    n = n % m;
    LL r = n;
    r = (n + 1) % m * r % m;
    r = pow(4*n-2, m-2, m) * r % m;
    return r;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    int T; cin >> T;
    while (T--) {
        LL n; cin >> n;
        n -= 1;
        cout << calc(n, 1000000007) << " " << calc(n, 1000000009) << '\n';
    }
}
