#include <iostream>
#include <vector>
using namespace std;
#define LL long long

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    int n; cin >> n;
    LL a, f, g;
    cin >> a;
    f = a;
    g = -a;
    for (int i=1; i<n; i++) {
        cin >> a;
        LL f1 = max(f, max(a + g, a));
        LL g1 = max(g, max(f - a, -a));
        f = f1;
        g = g1;
    }
    cout << f;
    return 0;
}
