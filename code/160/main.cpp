#include <iostream>
using namespace std;

const long long oo = 1ll << 62;

int main() {
    cin.tie(0); ios::sync_with_stdio(0);
    int n; cin >> n;
    long long f0 = 0, f1 = oo, f2;
    for (; n > 1; n--) {
        int x; cin >> x;
        f2 = min(f0, f1) + x;
        f0 = f1;
        f1 = f2;
    }
    cout << f1 << endl;
}
