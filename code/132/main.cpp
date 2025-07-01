#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    int T; cin >> T;
    while (T--) {
        int n; cin >> n;
        vector<int> a(n);
        for (int &x: a) cin >> x;
        vector<int> l(n), r(n);
        vector<int> stack;
        for (int i=0; i<n; i++) {
            while (!stack.empty() && a[stack.back()] >= a[i]) stack.pop_back();
            if (stack.empty()) l[i] = -1;
            else l[i] = stack.back();
            stack.push_back(i);
        }
        stack.clear();
        for (int i = n-1; i>=0; i--) {
            while (!stack.empty() && a[stack.back()] >= a[i]) stack.pop_back();
            if (stack.empty()) r[i] = n;
            else r[i] = stack.back();
            stack.push_back(i);
        }
#define res(i) (a[i]*(r[i]-l[i]-1))
        int u = 0;
        for (int i=1; i<n; i++) if (res(u) < res(i)) u = i;
        cout << res(u) << ' ' << l[u] + 2 << ' ' << r[u] << '\n';

    }
    return 0;
}
