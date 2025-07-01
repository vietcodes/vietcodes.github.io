#include <iostream>
#include <vector>
using namespace std;

void minimize(int &a, int b) {
    if (a > b) a = b;
}
void maximize(int &a, int b) {
    if (a < b) a = b;
}
typedef void (*func)(int &, int);

struct Fenwick {
    int n, init;
    vector<int> f, a;
    func update;

    Fenwick(int n, int val, func func):
        n(n), init(val),
        f(n+1, val), a(n+1),
        update(func) {}

    int get(int l, int r) {
        int result = init;
        while (l <= r) {
            if (r-(r&-r) >= l) update(result, f[r]), r -= r&-r;
            else update(result, a[r]), r -= 1;
        }
        return result;
    }
    void set(int i, int x) {
        a[i] = x;
        for (; i<=n; i += i&-i) update(f[i], x);
    }
};

int main() {
    ios::sync_with_stdio(false); cin.tie(0);

    int n, q; cin >> n >> q;

    Fenwick fmax(n, 0, maximize);
    Fenwick fmin(n, 1e8, minimize);

    for (int i=1; i<=n; i++) {
        int x; cin >> x;
        fmax.set(i, x);
        fmin.set(i, x);
    }

    while (q--) {
        int l, r; cin >> l >> r;
        cout << fmax.get(l, r) - fmin.get(l, r) << endl;
    }

    return 0;
}
