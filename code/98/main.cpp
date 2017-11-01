#include <iostream>
using namespace std;

#define ll long long
#define for(i,a,b) for (int i=a; i<b; i++)

bool check(int a, int b, int s) {
    int x = a & b;
    int y = (~a & ~b) & s-1;
    return !(x & x>>1) && !(y & y>>1);
}

ll solve(int m, int n) {
    int s = 1<<n;
    ll f[m][s];
    for(i,0,s) f[0][i] = 1;

    for(i,1,m) for(j,0,s) {
        f[i][j] = 0;
        for(k,0,s) if (check(j,k,s)) {
            f[i][j] += f[i-1][k];
        }
    }

    ll res = 0;
    for(i,0,s) res += f[m-1][i];
    return res;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    int T; cin >> T;
    while (T--) {
        int m, n;
        cin >> m >> n;
        cout << solve(max(m, n), min(m, n)) << '\n';
    }
    return 0;
}
