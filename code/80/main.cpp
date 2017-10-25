#include <string>
#include <vector>
#include <iostream>
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

    string s = b + ' ' + a;
    vector<int> z = z_algo(s.data(), s.size());

    int m = b.size();
    for (int i=m; i<(int)z.size(); i++) {
        if (z[i] == m) cout << i-m << ' ';
    }
    return 0;
}
