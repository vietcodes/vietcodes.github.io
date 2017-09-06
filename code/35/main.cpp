#include <vector>
#include <iostream>
using namespace std;
#define ULL unsigned long long
const ULL BASE = 1000000000;
typedef vector<ULL> BigInt;

void println(const BigInt& a) {
    int L = a.size();
    printf("%llu", a[L - 1]);
    for (int i = L - 2; i >= 0; i--) printf("%09llu", a[i]);
    printf("\n");
}
BigInt operator + (const BigInt& a, const BigInt& b) {
    BigInt c; ULL carry = 0;
    for (size_t i = 0; i < a.size() || i < b.size(); i++) {
        if (i < a.size()) carry += a[i];
        if (i < b.size()) carry += b[i];
        c.push_back(carry % BASE); carry /= BASE;
    }
    if (carry) c.push_back(carry); return c;
}
BigInt operator * (const BigInt& a, const int mul) {
    BigInt c; ULL carry = 0;
    for (size_t i = 0; i < a.size(); i++) {
        carry += a[i] * mul; c.push_back(carry % BASE); carry /= BASE;
    }
    if (carry) c.push_back(carry); return c;
}
bool operator < (const BigInt& a, const BigInt& b) {
    if (a.size() != b.size()) return a.size() < b.size();
    for (int i = a.size() - 1; i >= 0; i--)
        if (a[i] != b[i]) return a[i] < b[i];
    return false;
}

BigInt f[201][201];

void prepare() {
    f[0][0] = {1};
    for (int i=1; i<=200; i++) {
    	f[i][0] = f[i-1][0];
        for (int j=1; j<i; j++) {
            f[i][j] = f[i-1][j]*(j+1) + f[i-1][j-1]*(i-j);
        }
    }

    for (int i=1; i<=200; i++) {
        for (int j=1; j<=200; j++) {
            f[i][j] = f[i][j] + f[i][j-1];
        }
    }
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    prepare();
    int T; cin >> T;
    while (T--) {
        int n, s, w, m, bmin, bmax;
        cin >> n >> s >> w >> m >> bmin >> bmax;
        vector<int> a(n);
        for (int &a: a) cin >> a, a *= m;
        vector<vector<BigInt>> g(n+1, vector<BigInt>(s+1));
        vector<vector<bool>> x(n+1, vector<bool>(s+1, false));
        x[0][0] = true;
        for (int i=1; i<=n; i++) for (int j=1; j<=s; j++) {
            int b = 0;
            for (int k=i-1; k>=0; k--) {
                b += a[k];
                if (b > bmax) break;
                if (bmin <= b && x[k][j-1]) {
                    x[i][j] = true;
                    BigInt tmp = g[k][j-1] + f[i-k][w];
                    if (g[i][j] < tmp) g[i][j] = tmp;
                }
            }
        }
        println(g[n][s]);
    }
    return 0;
}
