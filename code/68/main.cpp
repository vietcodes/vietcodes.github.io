#include <iostream>
#include <queue>
using namespace std;

#define LL long long
typedef priority_queue<LL, vector<LL>, greater<LL>> min_heap;

void query() {
    int n; cin >> n;
    min_heap heap;
    while (n--) {
        LL x; cin >> x;
        heap.push(x);
    }

    LL res = 0;
    while (heap.size() > 1) {
        int a = heap.top(); heap.pop();
        int b = heap.top(); heap.pop();
        res += a + b;
        heap.push(a + b);
    }

    cout << res << '\n';
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    int T; cin >> T;
    while (T--) query();
    return 0;
}
