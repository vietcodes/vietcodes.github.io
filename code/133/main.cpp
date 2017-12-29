#include <iostream>
#include <vector>
#include <string>
using namespace std;

vector<int> z_algo(const char *s, int n) {
    vector<int> z(n);

    int l = 0, r = 0;
    for (int i=1; i<n; i++) {
        if (z[i-l] < r-i+1) z[i] = z[i-l];
        else {
            r = max(r, i);
            while (s[r-i] == s[r]) r += 1;
            z[i] = r - i;
            r -= 1;
            l = i;
        }
    }

    return z;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    string a, b; cin >> a >> b;
    string c = b + " " + a;
    vector<int> z = z_algo(c.data(), c.size());
    int n = a.size(), m = b.size(), k = z.size();
    for (int i=m+1; i<k; i++) if (z[i] == n-(i-m-1)) {
        cout << a.substr(0, i-m-1) + b;
        return 0;
    }
    cout << a + b;
    return 0;
}
