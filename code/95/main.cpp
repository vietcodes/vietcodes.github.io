#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

typedef vector<vector<int>> dsk;

struct bit {
    int n;
    vector<int> f;
    bit(int n): n(n), f(n+1,0) {}
    void up(int i) {
        for (; i<=n; i += i&-i) f[i]++;
    }
    int get(int i) {
        int r = 0;
        for (; i>0; i -= i&-i) r += f[i];
        return r;
    }
    int get(int l, int r) { return get(r) - get(l-1); }
};

int top = 0;
int L[100000], R[100000];

void dfs(int u, const dsk &con) {
    L[u] = ++top;
    for (int v: con[u]) dfs(v, con);
    R[u] = ++top;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);

    int n; cin >> n;
    dsk con(n);
    vector<pair<int, int>> C(n);
    cin >> C[0].first;
    for (int i=1; i<n; i++) {
        int cha;
        cin >> cha >> C[i].first;
        con[cha-1].push_back(i);
    }
    dfs(0, con);

    for (int i=0; i<n; i++) C[i].second = i;
    sort(C.begin(), C.end());

    bit bit(2*n);
    long long res = 0;
    for (int i=1, k=0; i<n; i++) {
        for (; C[k].first < C[i].first; k++) bit.up(L[C[k].second]);
        int u = C[i].second;
        long long count = bit.get(L[u], R[u]);
        res += count * (count-1) / 2;
    }

    cout << res;
    return 0;
}
