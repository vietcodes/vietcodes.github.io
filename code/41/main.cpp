#include <cstdio>
using namespace std;
#define LL long long

LL a[1001][1001];

inline LL sum(int x, int y, int u, int v) {
    return a[u][v] - a[x-1][v] - a[u][y-1] + a[x-1][y-1];
}

inline LL abs(LL l) {
    return l<0?-l:l;
}

inline LL min(LL a, LL b) {
    return a<b?a:b;
}

LL query(int x, int y, int u, int v) {
    LL res = 1ll << 60;
    LL full = sum(x,y,u,v);
    LL half = full / 2;
    // Cắt dọc
    int l = y, r = v;
    while (l<=r) {
        int k = (l+r) / 2;
        if (sum(x,y,u,k) < half) l = k + 1;
        else r = k-1;
    }
    res = min(res, min(
                abs(full - 2*sum(x,y,u,l)),
                abs(full - 2*sum(x,y,u,r))
            ));
    // Cắt ngang
    l = x, r = u;
    while (l<=r) {
        int k = (l+r) / 2;
        if (sum(x,y,k,v) < half) l = k + 1;
        else r = k - 1;
    }
    res = min(res, min(
                abs(full - 2*sum(x,y,l,v)),
                abs(full - 2*sum(x,y,r,v))
            ));
    return res;
}

int main() {
    int m, n, k;
    scanf("%d%d%d", &m, &n, &k);
    for (int i=1; i<=m; i++) {
        for (int j=1; j<=n; j++) {
            scanf("%lld", &a[i][j]);
            a[i][j] = a[i][j] + a[i-1][j] + a[i][j-1] - a[i-1][j-1];
        }
    }
    while (k--) {
        int x, y, u, v;
        scanf("%d%d%d%d", &x, &y, &u, &v);
        printf("%lld\n", query(x,y,u,v));
    }
    return 0;
}
