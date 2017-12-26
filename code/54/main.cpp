#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

bool test(int a) {
    int k = sqrt(2*a);
    return k*(k+1) / 2 == a;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    int n; cin >> n;
    vector<int> a(n);
    for (int &a: a) cin >> a;

    int l = 0, max_l = 0;
    for (int i=0; i<n; i++) {
        if (test(a[i])) {
            if (i>0 && a[i]>=a[i-1]) l += 1;
            else l = 1;
            max_l = max(max_l, l);
        } else l = 0;
    }

    cout << max_l;

    return 0;
}
