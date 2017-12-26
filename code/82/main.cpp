#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false); cin.tie(0);

    int n; cin >> n;
    vector<int> a(n);
    for (int &x: a) cin >> x;

    vector<int> f(n+1), b(n+1, INT_MAX);
    b[0] = INT_MIN;
    int result = 0;
    for (int x: a) {
        int k = lower_bound(b.begin(), b.end(), x) - b.begin();
        b[k] = x;
        result = max(result, k);
    }

    cout << result;
    return 0;
}
