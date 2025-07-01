#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
#define LL long long

class Bit {
    int m;
    vector<LL> f;

    public:
    Bit(int m): m(m), f(m + 1) {}

    // Tính tổng từ i đến m
    LL get(int i) {
        LL res = 0;
        for (; i <= m; i += i&-i) res += f[i];
        return res;
    }

    // Tăng 1 tại vị trí i
    void up(int i) {
        for (; i >= 1; i -= i&-i) f[i] += 1;
    }
};

int main() {
    ios::sync_with_stdio(false); cin.tie(0);

    int tests; cin >> tests;
    for (int test = 1; test <= tests; test++) {
        int n, m, k;
        cin >> n >> m >> k;
        vector<pair<int, int>> roads(k);
        for (auto &pair: roads) {
            cin >> pair.first >> pair.second;
        }

        sort(roads.begin(), roads.end());

        Bit bit(m);
        LL res = 0;
        for (auto &pair: roads) {
            int to = pair.second;
            res += bit.get(to + 1);
            bit.up(to);
        }
        cout << "Test case " << test << ": " << res << "\n";
    }
}
