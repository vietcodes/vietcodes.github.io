#include <iostream>
#include <vector>
#include <array>
using namespace std;

const int M = 500;

int pack(int u, int v) {
    return u*M + v;
}

array<int, 3> ke1(int x) {
    return {{x+1, x+M, x+M+1}};
}

array<int, 3> ke2(int x) {
    return {{x-1, x+M, x+M-1}};
}

bool inBound(int u, int n) {
    int x = u / M, y = u % M;
    return 0 <= x && x < n && 0 <= y && y < n;
}

vector<int> next(vector<int> &&q, array<int, 3> (*ke)(int), vector<int> &state, int step, int n) {
    vector<int> res;
    for (auto q: q) for (auto q: ke(q)) {
        if (inBound(q, n) && state[q] != step && state[q] >= 0) {
            state[q] = step;
            res.push_back(q);
        }
    }
    return res;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    int n, k; cin >> n >> k;
    vector<int> state1(M*M, 0), state2(M*M, 0);
    while (k--) {
        int u, v; cin >> u >> v;
        u--, v--;
        state1[pack(u, v)] = state2[pack(u, v)] = -1;
    }
    vector<int> q1(1, pack(0, 0)), q2(1, pack(0, n-1));
    int step = 0;
    while (true) {
        step++;
        q1 = next(move(q1), ke1, state1, step, n);
        q2 = next(move(q2), ke2, state2, step, n);
        for (auto u: q1) if (state2[u] == step) {
            cout << step; 
            return 0;
        };
    }
    return 0;
}
