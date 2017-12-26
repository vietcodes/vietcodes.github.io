#include <iostream>
#include <vector>
using namespace std;
 
typedef vector<vector<int>> dsk;
struct pack {int count, s, d; };
 
pack dfs(int u, int p, const dsk &ke) {
    int count = 0, ss = 0, ws = 0, d = 0;
    for (int v : ke[u]) if (v != p) {
        pack r = dfs(v, u, ke);
        count += r.count;
        d = max(d, r.d);
        if (r.s) ss++;
        else ws++;
    }
 
    int ns, nd;
    if (ss == 0 || d == 2) {
        count++;
        ns = 1;
        if (ss || ws) nd = 0;
        else nd = 1;
    } else {
        ns = 0;
        if (d || ss < 2) nd = 2;
        else nd = 0;
    }
    return {count, ns, nd};
}
 
int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    int T; cin >> T;
    while (T--) {
        int n; cin >> n;
        if (n == 1) {
            cout << "-1\n";
            continue;
        }
        dsk ke(n);
        while (--n) {
            int u, v; cin >> u >> v;
            u--, v--;
            ke[u].push_back(v);
            ke[v].push_back(u);
        }
        pack r = dfs(0, -1, ke);
        if (r.d > 0) r.count++;
        cout << r.count << '\n';
    }
    return 0;
}
