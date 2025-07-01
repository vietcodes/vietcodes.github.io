#include <iostream>
using namespace std;

#define ll long long
#define M 20122007

ll pow(ll n) {
    ll res = 1;
    ll x = 3;
    while (n > 0) {
        if (n & 1) (res *= x) %= M;
        n >>= 1;
        (x *= x) %= M;
    }
    return res;
}

int main() {
    ll a;
    cin >> a;
    ll res = 1;
    for (ll i=1; i*i <= a; i++) if (a % i == 0) {
        if (a / i != i) (res *= pow(a / i) - 1) %= M;
        (res *= pow(i) - 1) %= M;
    }
    cout << res;
    return 0;
}
