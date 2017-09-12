#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false); cin.tie(0);

    int n, m; cin >> n >> m;
    vector<int> a(n);
    for (int &a: a) cin >> a;

    sort(a.begin(), a.end());

    int res = a[0] + a[1] + a[2];
    for (int i = 2; i<n; i++) {
        int s = m - a[i];

        int j = i-1, k = 0;
        while (j > k) {
            while (j > k && a[j]+a[k] > s) j--;
            while (j > k && a[j]+a[k] <= s) {
                res = max(res, a[i] + a[j] + a[k]);
                k++;
            }       
        }
    }

    cout << res;
    return 0;
}
