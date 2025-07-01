#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;

bool moves(int k, const vector<int> &x, const vector<int> &t, int n) {
    struct pack { int l, r; };
    vector<pack> f(n);
    for (int i=0; i<n; i++) {
        int d = k / t[i];
        f[i].l = x[i] - d;
        f[i].r = x[i] + d;
    }
    sort(f.begin(), f.end(), [](pack &a, pack &b) { return a.l < b.l; });
    auto it = f.begin();
    priority_queue<int, vector<int>, greater<int>> heap;
    for (int i=1; i<=n; i++) {
        while (it != f.end() && it->l <= i) {
            if (it->r >= i) heap.push(it->r);
            it++;
        }
        while (!heap.empty() && heap.top() < i) heap.pop();
        if (heap.empty()) return false;
        heap.pop();
    }
    return true;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    int n; cin >> n;
    vector<int> x(n), t(n);
    for (int i=0; i<n; i++) cin >> x[i] >> t[i];
    int l = 0, r = 1000000000;
    while (l<=r) {
        int k = (l + r) / 2;
        if (moves(k, x, t, n)) r = k - 1;
        else l = k + 1;
    }
    cout << l << endl;
    return 0;
}
