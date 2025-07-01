#include <cstdio>
#include <vector>
using namespace std;
#define UL unsigned long long
#define BASE 1000000000000000000ull
struct BigInt { UL h, l; };
const BigInt zero = {0, 0};

void operator += (BigInt &a, const BigInt b) {
    a.l += b.l;
    if (a.l > BASE) a.l -= BASE, a.h += 1;
    a.h += b.h;
}
void operator -= (BigInt &a, const BigInt b) {
    if (a.l < b.l) a.l += BASE-b.l, a.h -= 1;
    else a.l -= b.l;
    a.h -= b.h;
}
void print(BigInt a) {
    if (a.h == 0) printf("%llu", a.l);
    else printf("%llu%018llu", a.h, a.l);
}

int main() {
    int s, n;
    scanf("%d%d", &s, &n);

    vector<BigInt> f(s+1, zero), d(s+1, zero);
    f[0].l = 1;
    for (int k=0; k<n; k++) {
        int c, m;
        scanf("%d%d", &c, &m);

        for (int i=c; i<=s; i++) {
            d[i] = f[i-c];
            d[i] += d[i-c];
            if (i >= c*(m+1)) {
                d[i] -= f[i-c*(m+1)];
            }
        }

        for (int i=0; i<=s; i++) f[i] += d[i], d[i] = zero;
    }

    print(f[s]);
    return 0;
}
