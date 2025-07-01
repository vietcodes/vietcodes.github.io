#include <cstdio>
#include <vector>
using namespace std;
#define LL long long

vector<LL> prime_factor(LL x) {
    vector<LL> res;
    LL d = 2;
    while (d*d <= x) {
        if (x % d == 0) {
            LL tmp = 1;
            while(x % d == 0) x /= d, tmp *= d;
            res.push_back(tmp);
        }
        d++;
    }
    if (res.empty() || x > 1) res.push_back(x);
    return res;
}

LL gcd(LL a, LL b) {
    LL r;
    while (b != 0) r=a%b, a=b, b=r;
    return a;
}

void test(const vector<LL> &a, LL k) {
    vector<LL> p = prime_factor(k);

    vector<LL> b(p.size(), 0);
    for (LL a: a) {
        for (int i=0; i<(int)b.size(); i++) {
            if (a % p[i] == 0) b[i] = gcd(a, b[i]);
        }
    }

    bool ok = true;
    for (LL b: b) ok &= (b > 0 && k % b == 0);

    printf("%s\n", ok? "YES":"NO");
}

int main() {
    int T; scanf("%d", &T);
    while (T--) {
        int n; scanf("%d", &n);
        vector<LL> a(n);
        for (LL &a: a) scanf("%lld", &a);
        LL k; scanf("%lld", &k);
        test(a, k);
    }
    return 0;
}
