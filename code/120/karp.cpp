#include <iostream>
#include <vector>
#include <queue>
#include <climits>
using namespace std;

int n, s, t;

struct edge {
    int s, t;
    int cap, flow;
    edge *rev;
    edge(int s, int t, int cap): s(s), t(t), cap(cap) {
        flow = 0;
        rev = NULL;
    }
};

vector<vector<edge*>> ke;

int edmonds_karp() {
    int flow = 0;
    vector<edge*> trace(n+1);
    do {
        trace.assign(trace.size(), NULL);
        queue<int> q;
        q.push(s);
        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (edge *e: ke[u]) {
                if (!trace[e->t] && e->t != s && e->cap > e->flow) {
                    trace[e->t] = e;
                    q.push(e->t);
                }
            }
        }

        if (trace[t]) {
            int df = INT_MAX;
            for (edge *e = trace[t]; e; e = trace[e->s]) {
                df = min(df, e->cap - e->flow);
            }
            for (edge *e = trace[t]; e; e = trace[e->s]) {
                e->flow += df;
                e->rev->flow -= df;
            }
            flow += df;
        }
    } while(trace[t]);

    return flow;
}

void add_edge(int u, int v, int cap) {
    edge* e = new edge(u, v, cap);
    edge* rev = new edge(v, u, 0);
    e->rev = rev;
    rev->rev = e;
    ke[u].push_back(e);
    ke[v].push_back(rev);
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    int m;
    cin >> n >> m >> s >> t;
    ke.resize(n+1);
    while (m--) {
        int u, v, c;
        cin >> u >> v >> c;
        add_edge(u, v, c);
    }
    cout << edmonds_karp();
    return 0;
}
