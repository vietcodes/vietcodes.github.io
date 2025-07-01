#include <iostream>
using namespace std;
#define ll long long

ll count(ll n) {
    return n / 30 + n / 12 - (n / 60) * 2;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    int T; cin >> T;
    while (T--) {
        ll a, b;
        cin >> a >> b;
        cout << count(b) - count(a-1) << '\n';
    }
}
