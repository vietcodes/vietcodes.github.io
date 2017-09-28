#include <iostream>
using namespace std;

int divisor_sum(int x) {
    if (x==1) return 0;
    int sum = 1;
    for (int d=2; d*d <= x; d++) {
        if (x % d == 0) {
            sum += d;
            if (x/d != d) sum += x/d;
        }
    }
    return sum;
}

int main() {
    int l, r; cin >> l >> r;
    int count = 0;
    for (int i=l; i<=r; i++) if (divisor_sum(i) > i) count++;
    cout << count;
    return 0;
}
