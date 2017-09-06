#include <iostream>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    string s; cin >> s;

    sort(s.begin(), s.end());
    string res;
    int count = 0;
    do {
        count++;
        res += s;
        res += '\n';
    } while(next_permutation(s.begin(), s.end()));

    cout << count << '\n';
    cout << res;
    return 0;
}
