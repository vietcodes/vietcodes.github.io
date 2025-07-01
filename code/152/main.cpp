#include <iostream>
#include <tuple>
#include <vector>
#include <algorithm>
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
    ll s, d;
    s = __builtin_ctzll(n-1);
    d = (n-1) >> s;
    return witness_test(s, d, n, 2) && witness_test(s, d, n, 7) && witness_test(s, d, n, 61);
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    int T; cin >> T;
    vector<ll> inp(T);
    for (ll &x: inp) cin >> x;

    vector<ll> a = inp;
    sort(a.begin(), a.end());
    vector<ll> primes;
    primes.push_back(2);
    ll bound = primes.back() + 1;
    for (ll n: a) {
        for (ll p = n&1? n-2: n-1; p >= bound; p -= 2) {
            if (miller(p)) {
                primes.push_back(p);
                break;
            }
        }
        bound = n;
    }

    for (ll n: inp) {
        auto it = lower_bound(primes.begin(), primes.end(), n);
        it--;
        cout << *it << '\n';
    }
}

