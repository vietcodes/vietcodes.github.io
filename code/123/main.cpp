#include <cstdio>
#include <vector>
#include <queue>
using namespace std;

typedef vector<vector<int>> dsk;

int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    dsk ke(n+1);
    while (m--) {
        int u, v;
        scanf("%d%d", &u, &v);
        ke[u].push_back(v);
        ke[v].push_back(u);
    }

    vector<int> cha(n+1, 0);
    int res = 0;
    for (int i=1; i<=n; i++) if (!cha[i]) {
        queue<int> q;
        q.push(i);
        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (int v: ke[u]) if (v != cha[u]) {
                cha[v] = u;
                q.push(v);
                if (ke[u].size() < ke[v].size() - (u==i)) res++;
            }
        }
    }
    printf("%d", res);
    return 0;
}
