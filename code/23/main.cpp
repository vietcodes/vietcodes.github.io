#include <iostream>
using namespace std;

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    int n, m, k; cin >> n >> m >> k;
    string a; cin >> a;
    int res = 10000;
    while (k--) {
        string b; cin >> b;
        for (auto i = a.begin(); i != a.end(); i++) {
            auto j = i;
            int dis = 0;
            for (auto b: b) {
                if (j == a.end()) j = a.begin();
                if (*j != b) dis++;
                j++;
            }
            if (res > dis) res = dis;
        }
    }
    cout << res;
    return 0;
}
