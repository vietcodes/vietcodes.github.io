#include <bitset>
#include <vector>
#include <cstdio>
#include <memory>
#include <limits>
#include <algorithm>
using namespace std;

struct edge { int u, v; };
typedef vector< vector<int> > dsk;
typedef vector< bitset<50000> > bset;

inline void minimize(int &u, int v) { if (u > v) u = v; }

void tj(int i, int &num, const dsk &ke, vector<int> &map, vector<int>& idx, vector<int> &low, int &index, vector<int> &stack) {
    if (idx[i] >= 0) return;
    idx[i] = low[i] = index++;
    stack.push_back(i);
    for (auto j: ke[i]) {
        if (idx[j] < 0) {
            tj(j, num, ke, map, idx, low, index, stack);
            minimize(low[i], low[j]);
        } else if (map[j] < 0) minimize(low[i], idx[j]);
    }
    if (idx[i] == low[i]) {
        int j;
        do {
            j = stack.back(); stack.pop_back();
            map[j] = num;
        } while (j != i);
        num++;
    }
}

dsk* dag(vector<edge> &&canh, int &n, vector<int>& map, bset &set) {
    map.resize(n, -1);
    vector<int> idx(n, -1), low(n, numeric_limits<int>::max());
    vector<int> stack; stack.reserve(n);
    dsk ke(n);
    for (auto&x: canh) ke[x.u].push_back(x.v);
    int num = 0;
    int index = 0;
    for (int i=0; i<n; i++) tj(i, num, ke, map, idx, low, index, stack);
    n = num;
    set.resize(n);
    for (int i=0; i<n; i++) set[i].set(i);
    auto res = new dsk(n);
    for (auto&x: canh) {
        int a = map[x.u], b = map[x.v];
        if (!set[a].test(b)) {
            set[a].set(b);
            (*res)[a].push_back(b);
        }
    }
    return res;
}

void dfs(int i, vector<bool>& visited, bset &set, const dsk *ke) {
    if (visited[i]) return;
    visited[i] = true;
    for (auto j: (*ke)[i]) {
        dfs(j, visited, set, ke);
        set[i] |= set[j];
    }
}

void compute(const dsk *ke, bset &set) {
    int n = (int)ke->size();
    vector<bool> visited(n, false);
    for (int i=0; i<n; i++) dfs(i, visited, set, ke);
}

int main() {
    int m, n; scanf("%d%d", &n, &m);
    vector<edge> canh(m);
    while (m--) scanf("%d%d", &canh[m].u, &canh[m].v);
    vector<edge> query;
    int Q; scanf("%d", &Q);
    query.reserve(Q);
    canh.reserve(Q);
    while (Q--) {
        int t, a, b;
        scanf("%d%d%d", &t, &a, &b);
        if (t & 1) {
            n++;
            if (b & 1) canh.push_back({n, a});
            else canh.push_back({a, n});
        } else query.push_back({a, b});
    }
    for (auto&x: canh) x.u--, x.v--;
    for (auto&x: query) x.u--, x.v--;
    vector<int> map;
    bset set;
    auto ke = dag(move(canh), n, map, set);
    compute(ke, set);
    string output; output.reserve(query.size() * 4);
    for (auto&x: query) {
        int a = map[x.u], b = map[x.v];
        if (set[a].test(b)) output += "Yes\n";
        else output += "No\n";
    }
    printf("%s", output.data());
    delete ke;
    return 0;
}
