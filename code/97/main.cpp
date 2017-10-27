#include <iostream>
#include <valarray>
#include <vector>
#include <map>
using namespace std;

typedef valarray<int> val;
namespace std {
    bool operator < (const val &a, const val &b) {
        return a[0] < b[0] || (a[0] == b[0] && a[1] < b[1]);
    }
}

val sum(const vector<val> &a, int state) {
    val res = {{0, 0}};
    for (auto &x: a) {
        if (state & 1) res += x;
        state >>= 1;
    }
    return res;
}


int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    int n; cin >> n;

    int n1 = n / 2;
    vector<val> a(n1, val(2));
    for (val &x: a) cin >> x[0] >> x[1];

    int n2 = n - n1;
    vector<val> b(n2, val(2));
    for (val &x: b) cin >> x[0] >> x[1];

    val S(2); cin >> S[0] >> S[1];

    map<val, int> count;
    for (int state=0; state < 1<<n1; state++) count[sum(a, state)] += 1;

    int res = 0;
    for (int state=0; state < 1<<n2; state++) {
        val s = sum(b, state);
        if (count.count(S - s)) res += count[S - s];
    }
    cout << res;
    return 0;
}
