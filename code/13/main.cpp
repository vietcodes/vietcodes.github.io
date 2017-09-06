#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
using namespace std;

#define LL long long
struct pack { LL d, t, s; };
bool sort_cmp(pack &a, pack &b) {
    return a.s > b.s;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    int T; cin >> T;
    while (T--) {
        int n; LL d; cin >> n >> d;
        vector<pack> a(n);
        for (auto& i: a) cin >> i.d >> i.t >> i.s;
        sort(a.begin(), a.end(), sort_cmp);
        set<LL> s;
        for (LL i=1; i<=d; i++) s.insert(i);
        LL kq = 0;
        for (auto& i: a) {
            LL count = 0;
            auto first = s.lower_bound(i.d);
            auto it = first;
            for (; count < i.t && it != s.end(); it++) count++;
            s.erase(first, it);
            kq += (i.t - count) * i.s;
        }
        cout << kq << '\n';
    }
}
