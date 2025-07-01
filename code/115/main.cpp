#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    int n; cin >> n;
    vector<int> s(n+1);
    s[0] = 0;
    for (int i=1; i<=n; i++) {
        cin >> s[i];
        s[i] += s[i-1];
    }

    vector<bool> f(n+1);
    for (int i=n, smin = s[n]; i>0; i--) {
        f[i] = s[i-1] < smin;
        smin = min(smin, s[i-1]);
    }

    vector<bool> g(n+1);
    for (int i=1, smin = s[n]; i<=n; i++) {
        g[i] = s[i-1] < smin;
        smin = min(smin, s[i] + s[n]);
    }

    int count = 0;
    for (int i=1; i<=n; i++) count += f[i] && g[i];
    cout << count;

    return 0;
}
