#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios::sync_with_stdio(false); cin.tie(0);

    int n;
    cin >> n;
    vector<int> c(2 * n);
    int res = 0;
    for (int &c: c) {
        int a, b;
        cin >> a >> b;
        res += b;
        c = a - b;
    }
    sort(c.begin(), c.end());
    for (int i = 0; i < n; i++) {
        res += c[i];
    }
    cout << res;
    return 0;
}
