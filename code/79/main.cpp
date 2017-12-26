#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>
using namespace std;

#define LL long long
#define uchar unsigned char


LL reward(const LL a[8], int state) {
    LL reward = 0;
    int i = 0;
    while (state != 0) {
        reward += a[i] * (state & 1);
        state >>= 1;
        i += 1;
    }
    return reward;
}

int main() {
    vector<pair<int, vector<int>>> states;
    for (int i=0; i<256; i++) if ((i&(i>>1)) == 0) {
        states.push_back(make_pair(i, vector<int>()));
        for (int j=0; j<256; j++) if ((j&(j>>1)) == 0 && (i&j) == 0) {
            states.back().second.push_back(j);
        }
    }

    ios::sync_with_stdio(false); cin.tie(0);

    int n; cin >> n;
    vector<LL[8]> a(n);
    for (int j=0; j<8; j++) {
        for (int i=0; i<n; i++) cin >> a[i][j];
    }

    vector<LL> f(256, LLONG_MIN);
    vector<LL> f1(256);

    for (auto &p: states) {
        f[p.first] = reward(a[0], p.first);
    }

    for (int i=1; i<n; i++) {
        f1.assign(256, LLONG_MIN);
        for (auto &p: states) {
            LL max_reward = LLONG_MIN;
            for (int s: p.second) {
                max_reward = max(max_reward, f[s]);
            }
            f1[p.first] = max_reward + reward(a[i], p.first);
        }
        f.swap(f1);
    }

    LL result = *max_element(f.begin(), f.end());

    if (result == 0) {
        result = LLONG_MIN;
        for (LL *a: a) {
            result = max(result, *max_element(a, a + 8));
        }
    }

    cout << result;
    return 0;
}
