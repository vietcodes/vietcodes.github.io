#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    int T; cin >> T;
    while (T--) {
        string s; cin >> s;
        vector<char> a;
        for (auto c: s) if (c != '=') a.push_back(c);
        int n = (int)a.size();
        if (n == 0) cout << "1\n";
        else {
            vector<int> l(n);
            l[0] = 2;
            for (int i=1; i<n; i++) {
                if (a[i] == a[i-1]) l[i] = l[i-1] + 1;
                else l[i] = 2;
            }
            cout << *max_element(l.begin(), l.end()) << '\n';
        }
    }
    return 0;
}
