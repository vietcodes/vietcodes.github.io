#include <cstdio>
#include <vector>
using namespace std;
#define LL long long

int n, m;
vector<int> ke[100000];

void dfs(int u, vector<bool> &visited) {
    visited[u] = true;
    for (int v: ke[u]) if (!visited[v]) dfs(v, visited);
}

int count_ccs() {
    int c = 0;
    vector<bool> v(n, false);
    for (int i=0; i<n; i++) if (!v[i]) dfs(i, v), c++;
    return c;
}

int dfs1(int i, vector<int>& idx, vector<int> &low, vector<int> &trace, int &index, LL &res, int &nBridge) {
    int nChild = 0;
    index += 1;
    idx[i] = low[i] = index;
    for (int j: ke[i]) {
        if (!idx[j]) {
            trace[j] = i;
            int nChildJ = dfs1(j, idx, low, trace, index, res, nBridge);
            nChild += nChildJ;
            low[i] = min(low[i], low[j]);
            if (low[j] > idx[i]) {
                nBridge++;
                res += (LL)nChildJ * (LL)(n-nChildJ) - 1ll;
            }
        } else if (j != trace[i]) low[i] = min(low[i], idx[j]);
    }
    return nChild + 1;
}

void solve1() {
    int index = 0, nBridge = 0;
    LL res = 0;
    vector<int> idx(n, 0), low(n, 0), trace(n, 0);
    dfs1(0, idx, low, trace, index, res, nBridge);
    res += (LL)(m-nBridge) * ((LL)n * (LL)(n-1) / 2ll - (LL)m);
    printf("%lld", res);
}

void dfs2(int i, vector<int>& idx, vector<int> &low, vector<int> &trace, int &index, int &num_bridge) {
    index += 1;
    idx[i] = low[i] = index;
    for (int j: ke[i]) {
        if (!idx[j]) {
            trace[j] = i;
            dfs2(j, idx, low, trace, index, num_bridge);
            low[i] = min(low[i], low[j]);
            if (low[j] > idx[i]) num_bridge++;
        } else if (j != trace[i]) low[i] = min(low[i], idx[j]);
    }
}

void solve2() {
    int index = 0, nBridge = 0;
    vector<int> idx(n, 0), low(n, 0), trace(n, 0);
    dfs2(0, idx, low, trace, index, nBridge);
    int c1 = index;
    for (int i=0; i<n; i++) if (!idx[i]) {
        dfs2(i, idx, low, trace, index, nBridge);
        break;
    }
    LL res = (LL)(m-nBridge) * (LL)c1 * (LL)(n-c1);
    printf("%lld", res);
}


int main() {
    scanf("%d%d", &n, &m);
    for (int i=0; i<m; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        u--, v--;
        ke[u].push_back(v);
        ke[v].push_back(u);
    }

    int num_ccs = count_ccs();
    if (num_ccs > 2) printf("0");
    else if (num_ccs == 2) solve2();
    else solve1();
    return 0;
}
