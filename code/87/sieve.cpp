#include <iostream>
using namespace std;
#define N 100000
int sum[N+1];

int main() {
    for (int i=1; i<N; i++) {
        for (int j=2*i; j<=N; j += i) sum[j] += i;
    }
    int l, r;
    cin >> l >> r;
    int count = 0;
    for (int i=l; i<=r; i++) count += sum[i] > i;
    cout << count;
    return 0;
}
