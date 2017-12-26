#include <vector>
#include <iostream>
#include <deque>
using namespace std;

int compute(const vector<int> &a, const int d) {
    deque<int> q;
    int n = a.size();
    int kq = 10000000;
    for (int i=0; i<n; i++) {
        if (!q.empty() && q.front() <= i - d) q.pop_front();
        while (!q.empty() && a[q.back()]<=a[i]) q.pop_back();
        q.push_back(i);
        if (i>=d-1 && kq > a[q.front()]) kq = a[q.front()];
    }
    return kq;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    int n, Q; cin >> n >> Q;
    vector<int> a(n);
    for (auto& x: a) cin >> x;
    while (Q--) {
        int d; cin >> d;
        cout << compute(a, d) << "\n";
    }
    return 0;
}
