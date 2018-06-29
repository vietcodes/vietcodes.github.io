#include <iostream>
using namespace std;

int main() {
    long long f[31];
    f[0] = 1;
    f[1] = 0;
    for (int i=2; i <= 30; i++) {
        f[i] = 0;
        for (int j=i-2; j>=0; j -= 2) f[i] += 2 * f[j];
        f[i] += f[i-2];
    }

    int n;
    while (cin >> n) {
        if (n == -1) break;
        cout << f[n] << '\n';
    }
}
