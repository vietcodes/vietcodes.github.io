#include <iostream>
#include <vector>
using namespace std;

int sum(int s, const vector<int> &w) {
    int res = 0;
    for (int x: w) {
        if(s&1) res += x;
        s >>= 1;
    }
    return res;
}

int main() {
    int c, n; cin >> c >> n;
    vector<int> w(n);
    for (int &x: w) cin >> x;
    int res = 0;
    for (int i=0; i<1<<n; i++) {
        int weight = sum(i, w);
        if (weight <= c && weight > res) res = weight;
    }
    cout << res;
    return 0;
}
