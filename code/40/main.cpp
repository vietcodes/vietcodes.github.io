#include <bitset>
#include <iostream>
using namespace std;

#define N 503

int n, source, sink;
int G[N][N], F[N][N];
bitset<N> visited;
int change[N], trace[N], Q[N];

bool bfs() {
    visited.reset();
    int first(0), last(0);
    Q[first] = source;
    visited[source] = true;
    while (first <= last) {
        int u = Q[first++];
        for (int i=1; i<=n; i++) if (!visited[i]) {
            if (G[u][i] > F[u][i]) {
                change[i] = min(change[u], G[u][i] - F[u][i]);
                trace[i] = u;
            } else if (F[i][u] > 0) {
                change[i] = min(change[u], F[i][u]);
                trace[i] = -u;
            } else continue;

            if (i == sink) return true;
            Q[++last] = i;
            visited[i] = true;
        }
    }
    return false;
}

void update_flow() {
    int v = sink;
    while (v != source) {
        int u = trace[v];
        if (u > 0) F[u][v] += change[sink];
        else {
            u = -u;
            F[v][u] -= change[sink];
        }
        v = u;
    }
}

int max_flow() {
    change[source] = 1e9;
    int flow = 0;
    while (bfs()) {
        flow += change[sink];
        update_flow();
    }
    return flow;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    cin >> n;
    int C = 0;
    source = n + 1;
    sink = n + 2;
    for (int i=1; i<=n; i++) {
        int c; cin >> c;
        if (c < 0) G[i][sink] = -c;
        else {
            G[source][i] = c;
            C += c;
        }
    }

    int m; cin >> m;
    for(int i = 0; i < m; i++) {
        int p, q; cin >> p >> q;
        G[p][q] = C + 1;
    }

    n = n + 2;
    cout << C - max_flow();

    return 0;
}
