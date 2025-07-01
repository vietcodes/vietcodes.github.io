#include <iostream>
#include <tuple>
using namespace std;
typedef unsigned long long ll;

ll pow(ll a, ll n, ll m) {
    ll result = 1;
    a = a % m;
    while (n > 0) {
        if (n & 1) result = result * a % m;
        n >>= 1;
        a = a * a % m;
    }
    return result;
}

pair<ll, ll> factor(ll n) {
    ll s = 0;
    while ((n & 1) == 0) {
        s++;
        n >>= 1;
    }
    return {s, n};
}

bool witness_test(ll s, ll d, ll n, ll witness) {
    if (n == witness) return true;
    ll p = pow(witness, d, n);
    if (p == 1) return true;
    for (; s > 0; s--) {
        if (p == n-1) return true;
        p = p * p % n;
    }
    return false;
}

bool miller(ll n) {
    if (n < 2) return false;
    if ((n & 1) == 0) return n == 2;
    ll s, d;
    tie(s, d) = factor(n-1);
    return witness_test(s, d, n, 2) && witness_test(s, d, n, 7) && witness_test(s, d, n, 61);
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    int T; cin >> T;
    while (T--) {
        int m, n; cin >> m >> n;
        for (int i=m; i<=n; i++) if (miller(i)) {
            cout << i << '\n';
        }
        cout << '\n';
    }
}
