#include <iostream>
#include <cmath>
using namespace std;

bool is_prime(long long p) {
    if (p < 2) return false;
    if (p == 2) return true;
    if (p % 2 == 0) return false;
    for (long long d = 3; d * d <= p; d += 2) {
        if (p % d == 0) return false;
    }
    return true;
}

int main() {
    long long n; cin >> n;
    for (int q = 2; q < 64; q++) {
        long long p = round(exp(log(n) / q));
        long long nn = 1;
        for (int i=0; i < q; i++) nn *= p;
        if (nn == n && is_prime(p)) {
            cout << p << ' ' << q;
            return 0;
        }
    }
    cout << 0;
    return 0;
}
