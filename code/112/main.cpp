#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

#define LL long long

struct fenwick {
    int n;
    vector<LL> f;
    fenwick(int n): n(n), f(n+1, 0) {}
    void up(int i) {
        for (; i<=n; i+=i&-i) f[i]++;
    }
    LL get(int i) {
        LL res = 0;
        for (; i>0; i-=i&-i) res += f[i];
        return res;
    }
};

typedef pair<pair<int, int>, int> pack;
#define X first.first
#define Y first.second
#define ID second

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    int n; cin >> n;
    vector<pack> a(n);
    for (int i=0; i<n; i++) {
        cin >> a[i].X >> a[i].Y;
        a[i].ID = i;
    }
    sort(a.begin(), a.end());
    fenwick bit(100000);
    bit.up(a[0].Y);
    LL count_equal = 1;
    vector<int> count(n);
    for (int i=1; i<n; i++) {
        if (a[i].X != a[i-1].X || a[i].Y != a[i-1].Y) count_equal = 0;
        count_equal++;
        bit.up(a[i].Y);
        count[a[i].ID] = bit.get(a[i].Y) - count_equal;
    }
    for (int x: count) cout << x << '\n';
    return 0;
}
