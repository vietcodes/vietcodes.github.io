#include <iostream>
#include <vector>
using namespace std;

const int f[] = {1, 2, 3, 5, 1, 6, 0, 6, 6, 5, 4, 2, 6, 1, 0, 1};

int compute(int u, int v) {
    int k = (v - u + 1) / 16;
    if (k >= 2) return k * 16;
    // ở đây không nhất thiết phải là 20
    int lim = min(u + 20, v);
    for (int i=u+1; i<=lim; i++) if (f[i%16] == f[(i+15)%16]) return 2;
    return -1;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    int T; cin >> T;
    while (T--) {
        int u, v; cin >> u >> v;
        cout << compute(u - 1, v - 1) << '\n';
    }
    return 0;
}
