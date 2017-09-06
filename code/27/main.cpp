#include <iostream>
#include <vector>
#include <bitset>
using namespace std;

typedef vector<vector<int>> dsk;
typedef bitset<10001> bs;

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    int n, m; cin >> n >> m;
    dsk ke(n + 1);
    vector<bs> bits(n + 1);
    while (m--) {
        int u, v; cin >> u >> v;
        if (!bits[u].test(v)) {
            ke[u].push_back(v);
            ke[v].push_back(u);
            bits[v].set(u);
            bits[u].set(v);
        }
    }
    for (int u=1; u<=n; u++) {
        bs f;
        for (int v: ke[u]) {
            bits[v].reset(u);
            if ((f & bits[v]).any()) {
                f &= bits[v];
                int w = 1;
                while (!f.test(w)) w++;
                for (int x: ke[w]) if (bits[u].test(x)) {
                    cout << u << " " << v << " " << w << " " << x;
                    return 0;
                }
            } else {
                f |= bits[v];
            }
            bits[v].set(u);
        }
    }
    cout << -1;
    return 0;
}
