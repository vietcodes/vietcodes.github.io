#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
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
