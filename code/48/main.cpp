#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    int n, m, s;
    cin >> n >> m >> s;
    s -= 1;
    vector<vector<int>> ke(n);
    for (int i=0; i<m; i++) {
        int u, v;
        cin >> u >> v;
        ke[u-1].push_back(v-1);
    }

    vector<int> trace(n, -1), d(n, 0);
    vector<bool> stable(n, false);
    queue<int> q;
    q.push(s);
    trace[s] = s;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        // Duyệt qua các đỉnh kề với u, không
        // duyệt các cạnh bị trùng lặp.
        for (int v: ke[u]) if (trace[v] != u) {
            // Đỉnh v chưa được thăm
            if (trace[v] < 0) {
                q.push(v);
                trace[v] = u;
                d[v] = d[u] + 1;
                // Nếu u ổn định thì v cũng ổn định
                stable[v] = stable[u];
            } else if (d[u] + 1 == d[v]) {
                stable[v] = true;
            }
        }
    }

    int count = 0;
    for (int b: stable) if (b) count += 1;
    cout << count;
    return 0;
}
