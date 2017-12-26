#include <iostream>
#include <vector>
using namespace std;

#define LL long long

const LL M = 1000000000;

LL pow(LL x, int n) {
    if (n==0) return 1;
    int t = pow(x, n >> 1);
    t = t * t % M;
    if (n & 1) return t * x % M;
    return t;
}

int find(int x, int p) {
    int res = 0;
    while (x % p == 0) res++, x /= p;
    return res;
}

LL catalan(LL n) {
    vector<bool> prime(2*n+1, true);
    vector<int> count(2*n+1, 0);
    for (int i=2; i<=2*n; i++) if (prime[i]) {
        int c = 0;
        for (int j=i; j<=2*n; j+=i) {
            prime[j] = false;
            if (n+2 <= j) c += find(j, i);
            if (j<=n) c -= find(j, i);
        }
        count[i] = c;
    }
    LL res = 1;
    for (int i=1; i<=2*n; i++) {
        res = res * pow(i, count[i]) % M;
    }
    return res;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    int n, t; cin >> n >> t;
    vector<int> h(n);
    for (auto &h: h) cin >> h;
    int res = 2;
    for (int i=n-2; i >= 0; i--) {
        if (h[i] < h[i+1]) res++;
        else break;
    }
    cout << res << '\n' << catalan(n+1);
    return 0;
}
