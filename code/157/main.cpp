#include <iostream>
#include <string>
#include <vector>
using namespace std;

bool is_palindrome(const string &s, int l, int r) {
    while (l < r) {
        if (s[l] != s[r]) return false; 
        l++;
        r--;
    }
    return true;
}

int main() {
    string s; cin >> s;
    int n = s.size();
    s = " " + s;
    vector<int> f(n + 1, n);
    f[0] = 0;
    for (int i=1; i <= n; i++) {
        for (int j = i; j > 0; j--) {
            if (is_palindrome(s, j, i)) {
                f[i] = min(f[i], 1 + f[j-1]);
            }
        }
    }
    cout << f[n] << endl;
}
