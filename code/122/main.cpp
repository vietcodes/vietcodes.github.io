#include <iostream>
#include <climits>
#include <vector>
#include <queue>
using namespace std;
#define LL long long

bool minimize(int &x, int a) {
    if (x > a) {
        x = a;
        return true;
    }
    return false;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);

    int n; cin >> n;
    vector<int> a(n);
    for (int &x: a) cin >> x;

    vector<int> f(a[0], INT_MAX);
    f[0] = 0;
    queue<int> Q;
    Q.push(0);
    while(!Q.empty()) {
        int u = Q.front(); Q.pop();
        for (int v: a) {
            int x = (u+v) % a[0];
            if (minimize(f[x], f[u]+v)) Q.push(x);
        }
    }

    int q; cin >> q;
    while (q--) {
        int x; cin >> x;
        if (f[x%a[0]] <= x) cout << "TAK\n";
        else cout << "NIE\n";
    }
    return 0;
}
