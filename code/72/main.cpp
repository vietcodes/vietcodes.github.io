#include <iostream>
using namespace std;

int a[100001];

int main() {
    a[0] = 0;
    a[1] = 1;
    // Tính mảng A
    for (int i=2; i<=100000; i++) {
        // i lẻ
        if (i & 1) a[i] = a[i>>1] + a[(i>>1)+1];
        // i chẵn
        else a[i] = a[i>>1];
    }

    for (int i=2; i<=100000; i++) {
        a[i] = max(a[i], a[i-1]);
    }

    int t; cin >> t;
    while (t--) {
        int n; cin >> n;
        cout << a[n] << '\n';
    }
    return 0;
}
