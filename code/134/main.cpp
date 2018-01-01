#include <iostream>
#include <string>
#include <vector>
using namespace std;

uint64_t pow[1000000];

vector<uint64_t> make_hash(string &a) {
    vector<uint64_t> h(a.size());
    h[0] = a[0] - 'a';
    for (int i=1; i<(int)a.size(); i++) {
        h[i] = h[i-1] * 29 + (a[i]-'a');
    }
    return h;
}

uint64_t get_hash(const vector<uint64_t> &h, int l, int r) {
    if (l == 0) return h[r];
    return h[r] - h[l-1] * pow[r - l + 1];
}

int main() {
    pow[0] = 1;
    for (int i=1; i<1000000; i++) pow[i] = pow[i-1] * 29;

    ios::sync_with_stdio(false); cin.tie(0);
    int m, n; cin >> m >> n;
    string a, b; cin >> a >> b;
    auto ha = make_hash(a), hb = make_hash(b);
    int Q; cin >> Q;
    while (Q--) {
        int la, ra, lb, rb;
        cin >> la >> ra >> lb >> rb;
        la--, ra--, lb--, rb--;
        int len = min(ra-la+1, rb-lb+1);

        int low = 1, high = len;
        while (low <= high) {
            int k = (low + high) / 2;
            if (get_hash(ha, la, la+k-1) == get_hash(hb, lb, lb+k-1)) {
                low = k + 1;
            } else {
                high = k - 1;
            }
        }
        if (high == len) {
            if (ra-la == rb-lb) cout << '=';
            else if (ra-la < rb-lb) cout << '<';
            else cout << '>';
        } else {
            cout << (a[la+high]<b[lb+high]? '<':'>');
        }
    }
    return 0;
}
