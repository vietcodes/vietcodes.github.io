#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int manacher(const string &s) {
    string a;
    for (char c: s) a += '.', a += c;
    a += '.';
    int n = a.size();

    vector<int> f(n);
    int r = 0, c = 0;

    for (int i=0; i<n; i++) {
        f[i] = i<r? min(r-i, f[c-(i-c)]) : 0;
        while (a[i-f[i]-1] == a[i+f[i]+1]) f[i]++;
        if (i+f[i] > r) {
            r = i + f[i];
            c = i;
        }
    }

    return *max_element(f.begin(), f.end());
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    int n; cin >> n;
    string s; cin >> s;
    cout << manacher(s);
    return 0;
}
