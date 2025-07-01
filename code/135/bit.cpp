#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
#include <set>
using namespace std;
#define LL long long

struct SumIndex: private vector<LL> {
    SumIndex(const vector<int> &a) {
        set<LL> s;
        LL sum = 0;
        s.insert(sum);
        for (int x: a) sum += x, s.insert(sum);
        vector<LL>::operator=(vector<LL>(s.begin(), s.end()));
    }
    int operator()(LL x) const {
        return upper_bound(begin(), end(), x) - begin();
    }
    int size() const {
        return vector::size();
    }
};

struct Fenwick {
    int n, *f;
    Fenwick(int n): n(n), f(new int[n+1]()) {}
    ~Fenwick() { delete[] f; }
    void up(int i) {
        for (; i<=n; i += i&-i) f[i]++;
    }
    int sum(int i) {
        int res = 0;
        for (; i>0; i -= i&-i) res += f[i];
        return res;
    }
};

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    int n; cin >> n;
    LL l, r; cin >> l >> r;
    vector<int> a(n);
    for (int &x: a) cin >> x;
    SumIndex index(a);
    LL sum = 0, res = 0;
    Fenwick f(index.size());
    f.up(index(sum));
    for (int x: a) {
        sum += x;
        res += f.sum(index(sum - l)) - f.sum(index(sum-r-1));
        f.up(index(sum));
    }
    cout << res;
    return 0;
}
