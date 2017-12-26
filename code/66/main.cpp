#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

struct pack { int s, i; };
bool operator > (pack a, pack b) {
    return a.s > b.s;
}
typedef priority_queue<pack, vector<pack>, greater<pack>> min_heap;

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    int m, n, k; cin >> m >> n >> k;
    vector<int> a(m), b(n);
    for (int &a: a) cin >> a;
    for (int &b: b) cin >> b;

    sort(b.begin(), b.end());

    min_heap heap;
    vector<int> pair(m, 0);
    for (int i=0; i<m; i++) {
        heap.push({a[i]+b[0], i});
    }

    while (k--) {
        pack top = heap.top();
        cout << top.s << '\n';

        int i = top.i;
        heap.pop();
        pair[i] += 1;
        if (pair[i] < n) heap.push({a[i] + b[pair[i]], i});
    }

    return 0;
}
