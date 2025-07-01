#include <iostream>
using namespace std;

bool is_not_prime[200001];

int main() {
    is_not_prime[0] = is_not_prime[1] = true;
    for (int i = 2; i * i <= 200000; i++) if (!is_not_prime[i]) {
        for (int j = i * i; j <= 200000; j += i) is_not_prime[j] = true;
    }
    ios::sync_with_stdio(false); cin.tie(0);
    int a, b; cin >> a >> b;
    for (; a <= b; a++) if (!is_not_prime[a]) cout << a << '\n';
}
