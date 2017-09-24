#include <iostream>
#include <vector>
using namespace std;

#define LL long long

struct Fenwick {
    int n;
    vector<LL> f;
    Fenwick(int n): n(n), f(n+1, 0) {}
    void set(int i) {
        for (; i>=1; i -= i&(-i)) f[i]++;
    }
    LL get(int i) {
        LL result = 0;
        for (; i<=n; i += i&(-i)) result += f[i];
        return result;
    }
};

int main() {
    ios::sync_with_stdio(false); cin.tie(0);

    int n; cin >> n;
    Fenwick f(60000);
    LL result = 0;
    while (n--) {
        LL x; cin >> x;
        result += f.get(x+1);
        f.set(x);
    }
    cout << result;

    return 0;
}
