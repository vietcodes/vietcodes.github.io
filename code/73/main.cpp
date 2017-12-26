#include <iostream>
using namespace std;

#define For(i,a,b) for (int i=a; i<=b; i++)

int a[102][102];

int main() {
    ios::sync_with_stdio(false); cin.tie(0);

    int m, n;
    cin >> m >> n;
    For(j,0,n) a[0][j] = a[m+1][j] = -1e9;

    For(i,1,m) For(j,1,n) cin >> a[i][j];

    For(j,2,n) For(i,1,m) {
        a[i][j] += max(a[i-1][j-1], max(a[i][j-1], a[i+1][j-1]));
    }

    int result = -1e9;
    For(i,1,m) result = max(result, a[i][n]);

    cout << result;
    return 0;
}
