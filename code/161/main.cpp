#include <iostream>
#include <vector>
using namespace std;

int main() {
    cin.tie(0); ios::sync_with_stdio(0);
    int m, n; cin >> m >> n;

    vector<vector<int>>
        A(m+1, vector<int>(n+1, -1)),
        L(m+1, vector<int>(n+1)),
        C(m+1, vector<int>(n+1)),
        F(m+1, vector<int>(n+1));

    int result = 1;
    for (int i=1; i<=m; i++) {
        for (int j=1; j<=n; j++) {
            cin >> A[i][j];

            L[i][j] = A[i][j]==A[i][j-1]? L[i][j-1] + 1 : 1;
            C[i][j] = A[i][j]==A[i-1][j]? C[i-1][j] + 1 : 1;
            F[i][j] = A[i][j]==A[i-1][j-1]? min(min(L[i][j], C[i][j]), F[i-1][j-1] + 1) : 1;

            result = max(result, F[i][j]);
        }
    }
    cout << result << endl;
}
