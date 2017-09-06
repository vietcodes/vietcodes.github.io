#include <iostream>
#include <queue>
using namespace std;

// a[i][j] = true nếu ở ô (i, j) có quân cờ
bool a[201][201];
bool visited[201][201];

struct pack {
    int i, j; // Toạ độ của ô
    int d; // Độ dài đường đi
};

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    int n, m, p, q, s, t;
    cin >> n >> m >> p >> q >> s >> t;
    while (m--) {
        int x, y; cin >> x >> y;
        a[x][y] = true;
    }

    // BFS để tìm đường đi

    queue<pack> Q;
    // Thêm ô (p, q) vào queue với độ dài đường đi là 0
    Q.push({p, q, 0});
    visited[p][q] = true;
    while (!Q.empty()) {
        // Lấy u ở đầu queue, sau đó xóa u trong queue
        pack u = Q.front();
        int i = u.i, j = u.j;
        Q.pop();

        // Duyệt theo hướng đông nam
        for (int k=1; i+k<=n && j+k<=n; k++) if (!a[i+k][j+k]) {
            int i1 = i+k, j1 = j+k;

            // Ô (i1, j1) chưa được duyệt
            if (!visited[i1][j1]) {

                // Thêm (i1, j1) vào queue
                Q.push({i1, j1, u.d+1});
                visited[i1][j1] = true;

                // Nếu (i1, j1) là ô đích thì ta xuất kết quả,
                // rồi dừng chương trình
                if (i1==s && j1==t) {
                    cout << u.d+1;
                    return 0;
                }
            }
        } else break;

        // Duyệt theo hướng tây bắc
        for (int k=1; i-k>=1 && j-k>=1; k++) if (!a[i-k][j-k]) {
            int i1 = i-k, j1 = j-k;
            if (!visited[i1][j1]) {
                Q.push({i1, j1, u.d+1});
                visited[i1][j1] = true;
                if (i1==s && j1==t) {
                    cout << u.d+1;
                    return 0;
                }
            }
        } else break;

        // Duyệt theo hướng đông bắc
        for (int k=1; i-k>=1 && j+k<=n; k++) if (!a[i-k][j+k]) {
            int i1 = i-k, j1 = j+k;
            if (!visited[i1][j1]) {
                Q.push({i1, j1, u.d+1});
                visited[i1][j1] = true;
                if (i1==s && j1==t) {
                    cout << u.d+1;
                    return 0;
                }
            }
        } else break;

        // Duyệt theo hướng tây nam
        for (int k=1; i+k<=n && j-k>=1; k++) if (!a[i+k][j-k]) {
            int i1 = i+k, j1 = j-k;
            if (!visited[i1][j1]) {
                Q.push({i1, j1, u.d+1});
                visited[i1][j1] = true;
                if (i1==s && j1==t) {
                    cout << u.d+1;
                    return 0;
                }
            }
        } else break;
    }
    cout << -1;
    return 0;
}
