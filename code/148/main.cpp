#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
typedef long long ll;

struct pack {
    ll value;
    ll prime;
    int index;
};

bool operator < (const pack &a, const pack &b) {
    return a.value < b.value;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    int k, n; cin >> k >> n;
    vector<pack> p(k);
    for (pack &p: p) {
        cin >> p.prime;
        p.value = p.prime;
        p.index = -1;
    }
    vector<ll> res;
    while (n--) {
        auto i = min_element(p.begin(), p.end());
        res.push_back(i->value);
        for (pack &p: p) if (p.value == res.back()) {
            p.value = p.prime * res[++p.index];
        }
    }
    cout << res.back();
    return 0;
}
