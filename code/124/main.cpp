#include <iostream>
using namespace std;

#define UL unsigned long long
#define BASE 1000000000000000000ull
struct num { UL h, l; };
num operator + (num a, num b) {
    num res = {a.h + b.h, a.l + b.l};
    if (res.l > BASE) res.l -= BASE, res.h += 1;
    return res;
}
void println(num n) {
    if (n.h == 0) printf("%llu\n", n.l);
    else printf("%llu%018llu\n", n.h, n.l);
}

num fibo[101];

int main() {
    fibo[0] = fibo[1] = {0,1};
    for (int i=2; i<=100; i++) fibo[i] = fibo[i-1] + fibo[i-2];
    int T; cin >> T;
    while (T--) {
        int x;
        cin >> x;
        println(fibo[x]);
    }
}
