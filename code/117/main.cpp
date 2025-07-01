#include <iostream>
#include <cstring>
using namespace std;

int __s[2017][2017];
int& s(int i, int j) {
    int ii = 1001 + i - j;
    int jj = 1 + i + j;
    return __s[ii][jj];
}
int sum(int i, int j, int d) {
    i += d;
    {
        int ii = 1001 + i - j;
        int jj = 1 + i + j;
        i = ii;
        j = jj;
    }
    d = d<<1 | 1;
    return __s[i][j] - __s[i-d][j] - __s[i][j-d] + __s[i-d][j-d];
}

bool a[1000][1000];
short f[1000][1000];
short g[1000][1000];

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    int m, n;
    cin >> m >> n;
    for (int i=0; i<m; i++) {
        string s;
        cin >> s;
        for (int j=0; j<n; j++) a[i][j] = s[j] == '*';
    }

#define rep(i,n) for (int i=1; i<n; i++)
#define rrep(i,n) for (int i=n-2; i>=0; i--)
    rep(i,m) rep(j,n) {
        if (!(a[i][j] && a[i-1][j]) && !(a[i][j] && a[i][j-1])) {
            f[i][j] = min(f[i][j-1], f[i-1][j]) + 1;
        }
        g[i][j] = f[i][j];
    }
    memset(f, 0, sizeof(f));
    rep(i,m) rrep(j,n) {
        if (!(a[i][j] && a[i-1][j]) && !(a[i][j] && a[i][j+1])) {
            f[i][j] = min(f[i-1][j], f[i][j+1]) + 1;
        }
        g[i][j] = min(g[i][j], f[i][j]);
    }
    memset(f, 0, sizeof(f));
    rrep(i,m) rep(j,n) {
        if (!(a[i][j] && a[i+1][j]) && !(a[i][j] && a[i][j-1])) {
            f[i][j] = min(f[i+1][j], f[i][j-1]) + 1;
        }
        g[i][j] = min(g[i][j], f[i][j]);
    }
    memset(f, 0, sizeof(f));
    rrep(i,m) rrep(j,n) {
        if (!(a[i][j] && a[i+1][j]) && !(a[i][j] && a[i][j+1])) {
            f[i][j] = min(f[i+1][j], f[i][j+1]) + 1;
        }
        g[i][j] = min(g[i][j], f[i][j]);
    }
    for (int i=0; i<m; i++) g[i][0] = g[i][n-1] = 0;
    for (int i=0; i<n; i++) g[0][i] = g[m-1][i] = 0;

    for (int i=0; i<m; i++) for (int j=0; j<n; j++) {
        s(i,j) = a[i][j];
    }

    for (int i=1; i<2017; i++) for (int j=1; j<2017; j++) {
        __s[i][j] += __s[i-1][j] + __s[i][j-1] - __s[i-1][j-1];
    }


    int res = 0;
    int ii, jj, gg;
    for (int i=0; i<m; i++) for (int j=0; j<n; j++) {
        int tmp = sum(i, j, g[i][j]);
        if (res < tmp) {
            res = tmp;
            ii = i;
            jj = j;
            gg = g[i][j];
        }
    }

    printf("%d %d %d %d", res, ii+1, jj+1, gg);

    return 0;
}
