#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;

struct node {
    int name;
    int val;
};

struct edge {
    typedef vector<node>::const_iterator iter;
    iter from, to;
    int val;
    edge(const iter &from, const iter &to): from(from), to(to) {
        val = abs(from->val - to->val);
    }
};

bool operator < (const node &a, const node &b) {
    return a.val < b.val;
}

bool operator > (const edge &a, const edge &b) {
    return a.val > b.val;
}

typedef priority_queue<edge, vector<edge>, greater<edge>> minheap;

void push_edges(minheap& heap, vector<node> &a) {
    sort(a.begin(), a.end());
    a.push_back(node { -1, 0 });
    for (auto iter = a.begin(); iter != a.end() - 2; iter++) {
        heap.push(edge(iter, iter + 1));
    }
}

vector<int> init_set(int n) {
    vector<int> set(n);
    for (int i=0; i<n; i++) set[i] = i;
    return set;
}
int find_root(vector<int> &set, int u) {
    if (set[u] != u) set[u] = find_root(set, set[u]);
    return set[u];
}
bool join(vector<int> &set, int u, int v) {
    u = find_root(set, u);
    v = find_root(set, v);
    if (u == v) return false;
    if (rand() & 1) set[u] = v;
    else set[v] = u;
    return true;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    srand(time(NULL));

    int n; cin >> n;
    vector<node> a(n), b(n), c(n);
    for (int i=0; i<n; i++) {
        cin >> a[i].val >> b[i].val >> c[i].val;
        a[i].name = b[i].name = c[i].name = i;
    }

    minheap heap;
    push_edges(heap, a);
    push_edges(heap, b);
    push_edges(heap, c);

    auto set = init_set(n);
    long long res = 0;
    int count = 0;
    while (!heap.empty()) {
        if (count == n - 1) break;
        auto e = heap.top();
        heap.pop();
        if (join(set, e.from->name, e.to->name)) res += e.val, count += 1;
        auto next = e.to + 1;
        if (next->name != -1) heap.push(edge(e.from, next));
    }
    cout << res;
    return 0;
}
