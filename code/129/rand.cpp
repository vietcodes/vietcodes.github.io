#include <vector>
#include <cstdlib>
#include <ctime>
#include <iostream>
using namespace std;

struct dsu {
    vector<int> cha;
    dsu(int n): cha(n+1) {
        for (int i=0; i<=n; i++) cha[i] = i;
    }
    int find(int u) {
        if (cha[u] != u) cha[u] = find(cha[u]);
        return cha[u];
    }
    bool join(int u, int v) {
        if (find(u) == find(v)) return false;
        if (rand()&1) swap(u, v);
        cha[find(u)] = find(v);
        return true;
    }
};

int main() {
    srand(time(0));
    int n = 1000;
    int cnt = 0;
    dsu z(n);
    cout << n << '\n';
    while (cnt < n-1) {
        int u = rand()%n + 1;
        int v = rand()%n + 1;
        if (z.join(u, v)) {
            cout << u << ' ' << v << ' ' << rand()%1000000+1 << '\n';
            cnt++;
        }
    }
    int m = 1000000;
    cout << m << '\n';
    while (m > 0) {
        int u = rand()%n + 1;
        int v = rand()%n + 1;
        if (u != v) cout << u << ' ' << v << '\n', m--;
    }
    return 0;
}
