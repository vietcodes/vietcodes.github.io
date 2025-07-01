#include <iostream>
#include <vector>
#include <queue>
using namespace std;
#define LL long long

struct pack { LL f; int t; };
bool operator > (pack a, pack b) {
    return a.f > b.f;
}
typedef priority_queue<pack, vector<pack>, greater<pack>> min_heap;

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    int n; cin >> n;
    vector<int> t(n+1);
    vector<LL> p(n+1);
    for (int i=1; i<=n; i++) cin >> t[i] >> p[i];

    // Ở đây dùng mảng f để cho rõ nghĩa
    // Có thể dùng một biến long long f mà thôi.
    vector<LL> f(n+1, 0);
    min_heap heap;
    for (int i=1; i<=n; i++) {
        heap.push({f[i-1] + p[i], t[i]});
        while (!heap.empty() && heap.top().t < i) heap.pop();
        f[i] = heap.top().f;
    }

    cout << f[n];
    return 0;
}
