#include <iostream>
#include <vector>
using namespace std;

#define rep(i,a,b) for (int i=a; i<=b; i++)
#define N 101
int C[N][N];
int T[N][N];

vector<int> trace(int u, int v) {
    vector<int> path;
    do {
        path.push_back(u);
        u = T[u][v];
    } while (path.back() != v);
    return path;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    rep(i,1,N) rep(j,1,N) C[i][j] = 1e9;
    rep(i,1,N) C[i][i] = 0;

    int n, m, q;
    cin >> n >> m >> q;
    rep(_,1,m) {
        int u, v, w;
        cin >> u >> v >> w;
        C[u][v] = C[v][u] = w;
        T[u][v] = v;
        T[v][u] = u;
    }

    rep(k,1,n) rep(i,1,n) rep(j,1,n) {
        if (C[i][j] > C[i][k] + C[k][j]) {
            C[i][j] = C[i][k] + C[k][j];
            T[i][j] = T[i][k];
        }
    }

    rep(_,1,q) {
        int k,u,v;
        cin >> k >> u >> v;
        if (k) {
            auto path = trace(u,v);
            cout << path.size() << ' ';
            for (int u: path) cout << u << ' ';
        } else cout << C[u][v];
        cout << '\n';
    }
}
