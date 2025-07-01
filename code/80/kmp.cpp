#include <string>
#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    string a, b;
    cin >> a >> b;

    vector<int> p(b.size(), 0);
    int k = 0;
    for (int i=1; i<(int)b.size(); i++) {
        while (k > 0 && b[i] != b[k]) k = p[k-1];
        if (b[i] == b[k]) k++;
        p[i] = k;
    }

    k = 0;
    for (int i=0; i<(int)a.size(); i++) {
        while (k > 0 && a[i] != b[k]) k = p[k-1];
        if (a[i] == b[k]) k++;
        if (k == (int)b.size()) {
            cout << i-b.size()+2 << ' ';
            k = p[k-1];
        }
    }

    return 0;
}
