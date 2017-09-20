#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

vector<int> z_algo(const string &s) {
    int n(s.size());
    vector<int> z(n);

    int l(0), r(0);
    for (int i=1; i<n; i++) {
        if (i > r) {
            l = r = i;
            while (r<n && s[r-l]==s[r]) r += 1;
            z[i] = r - l;
            r -= 1;
        } else if (z[i-l] < r-i+1) {
            z[i] = z[i-l];
        } else {
            l = i;
            while (r<n && s[r-l]==s[r]) r += 1;
            z[i] = r - l;
            r -= 1;
        }
    }

    return z;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    
    string a, b;
    cin >> a >> b;

    vector<int> z = z_algo(b + ' ' + a);

    int m = b.size();
    for (int i=m; i<(int)z.size(); i++) {
        if (z[i] == m) {
            cout << i-m << ' ';
        }
    }
    return 0;
}
