#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <map>
#include <queue>
using namespace std;

#define LL long long

template<class T>
T C(T a, char op, T b) {
    if (op=='+') return a + b;
    if (op=='-') return a - b;
    if (op=='*') return a * b;
    throw 0;
}

template<class T, class P>
string V(T a, char op, P b) {
    stringstream ss;
    ss << '(' << a << op << b << ')';
    return string(ss.str());
}

vector<int> ke[2000];
int trace[2000];

int match(int n, int m) {
    vector<int> visited(n, -1);
    vector<int> ref(n);

    vector<int> mx(n, -1);
    vector<int> my(m, -1);
    int cnt = 0;

    for (int i=0; i<n; i++) if (mx[i] < 0) {
        struct { int u, v; } res = {-1, -1};

        queue<int> q;
        q.push(i);
        visited[i] = i;
        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (int v: ke[u]) {
                if (my[v] >= 0 && visited[my[v]] != i) {
                    q.push(my[v]);
                    ref[my[v]] = u;
                    visited[my[v]] = i;
                } else if (my[v] < 0) {
                    res = {u, v}; 
                    break;
                }
            }
            if (res.u >= 0) break;
        }

        if (res.u >= 0) {
            cnt++;
            while (true) {
                int vv = mx[res.u];
                mx[res.u] = res.v;
                my[res.v] = res.u;
                if (res.u == i) break;
                res = {ref[res.u], vv};
            };
        }
    }

    if (cnt < n) return cnt;

    for (int i=0; i<n; i++) if (mx[i] >= 0) {
        for (int j=0; j<(int)ke[i].size(); j++) {
            if (ke[i][j] == mx[i]) {
                trace[i] = j;
                break;
            }
        }
    } else trace[i] = -1;

    return cnt;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    int n; cin >> n; cin.ignore();
    vector<vector<string>> view(n);
    vector<vector<LL>> val(n);
    for (int i=0; i<n; i++) {
        string s;
        getline(cin, s);

        int cnt_op = 0;
        LL num[4] = {0,0,0,0};
        char op[4];
        for (char c: s) {
            if ('0' <= c && c <= '9') {
                num[cnt_op] *= 10;
                num[cnt_op] += c - '0';
            } else {
                op[cnt_op] = c;
                cnt_op++;
            }
        }

        if (cnt_op == 1) {
            val[i].push_back(C(num[0], op[0], num[1]));
            view[i].push_back(s);
        }
        if (cnt_op == 2) {
            val[i].push_back(C(C(num[0],op[0],num[1]),op[1],num[2]));
            val[i].push_back(C(num[0],op[0],C(num[1],op[1],num[2])));
            view[i].push_back(V(V(num[0],op[0],num[1]),op[1],num[2]));
            view[i].push_back(V(num[0],op[0],V(num[1],op[1],num[2])));
        }
        if (cnt_op == 3) {
            val[i].push_back(C(C(C(num[0],op[0],num[1]),op[1],num[2]),op[2],num[3])); // 0 1 2
            val[i].push_back(C(C(num[0],op[0],num[1]),op[1],C(num[2],op[2],num[3]))); // 0 2 1
            val[i].push_back(C(C(num[0],op[0],C(num[1],op[1],num[2])),op[2],num[3])); // 1 0 2
            val[i].push_back(C(num[0],op[0],C(C(num[1],op[1],num[2]),op[2],num[3]))); // 1 2 0
            val[i].push_back(C(num[0],op[0],C(num[1],op[1],C(num[2],op[2],num[3])))); // 2 1 0
            view[i].push_back(V(V(V(num[0],op[0],num[1]),op[1],num[2]),op[2],num[3])); // 0 1 2
            view[i].push_back(V(V(num[0],op[0],num[1]),op[1],V(num[2],op[2],num[3]))); // 0 2 1
            view[i].push_back(V(V(num[0],op[0],V(num[1],op[1],num[2])),op[2],num[3])); // 1 0 2
            view[i].push_back(V(num[0],op[0],V(V(num[1],op[1],num[2]),op[2],num[3]))); // 1 2 0
            view[i].push_back(V(num[0],op[0],V(num[1],op[1],V(num[2],op[2],num[3])))); // 2 1 0
        }

        /*
        cout << s << endl;
        for (int j=0; j<(int)ke[i].size(); j++) {
            cout << "\t" << view[i][j] << '=' << ke[i][j] << endl;
        }
        */
    }
    map<LL, int> map;
    for (int i=0; i<n; i++) {
        for (LL v: val[i]) {
            if (!map.count(v)) map.insert({v, (int)map.size()});
            ke[i].push_back(map[v]);
        }
    }

    if ((int)map.size() < n) { cout << "NO SOLUTION"; return 0; }
    int cnt = match(n, map.size());
    if (cnt < n) { cout << "NO SOLUTION"; return 0; }
    for (int i=0; i<n; i++) cout << view[i][trace[i]] << '\n';
    return 0;
}
