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
    // bits[u] sẽ có giá trị true tại các vị
    // trí tương ứng với các đỉnh kề với u
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
        // f lưu các đỉnh kề với các đỉnh kề của u
        bs f;
        for (int v: ke[u]) {
            bits[v][u] = false;

            // lệnh dưới kiểm tra xem f và bits[v]
            // có chung bit 1 nào không.
            if ((f & bits[v]).any()) {
                // trường hợp có ít nhất 1 bit 1 chung,
                // ta sẽ có được chu trình:
                //     u
                //    / \
                //   x   v
                //    \ /
                //     w
                // truy vết tìm w và x, sau đó xuất kết quả
                f &= bits[v];
                int w = 1;
                while (!f[w]) w++;
                for (int x: ke[w]) if (bits[u][x]) {
                    cout << u << " " << v << " " << w << " " << x;
                    return 0;
                }
            } else {
                // cập nhật lại f
                f |= bits[v];
            }

            bits[v][u] = true;
        }
    }
    cout << -1;
    return 0;
}
