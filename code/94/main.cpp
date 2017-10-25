#include <iostream>
#include <vector>
using namespace std;
#define rep(i,a,b) for (int i=a; i<=b; i++)

int c[101][101];
int trace[101][101];

int main() {
    ios::sync_with_stdio(false); cin.tie(0);

    int n,m,q;
    cin >> n >> m >> q;
    rep(i,1,n) rep(j,1,n) c[i][j]=1e9;
    rep(i,1,n) c[i][i] = 0, trace[i][i] = i;
    rep(_,1,m) {
        int u, v, w;
        cin >> u >> v >> w;
        c[u][v] = w;
        c[v][u] = w;
        trace[u][v] = v;
        trace[v][u] = u;
    }


    rep(k,1,n) rep(i,1,n) rep(j,1,n) {
        if (c[i][j] > c[i][k] + c[k][j]) {
            c[i][j] = c[i][k] + c[j][k];
            trace[i][j] = trace[i][k];
        }
    }

    rep(_,1,q) {
        int k, u, v;
        cin >> k >> u >> v;
        if (k) {
            vector<int> path;
            do {
                path.push_back(u);
                u = trace[u][v];
            } while (path.back() != v);
            cout << path.size() << ' ';
            for (int x: path) cout << x << ' ';
        } else cout << c[u][v];
        cout << '\n';
    }

    return 0;
}
