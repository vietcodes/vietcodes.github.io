#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    int n; cin >> n;
    vector<int> a(n);
    for (int &x: a) cin >> x;

    int result = 1;
    for (int i=0; i<n; i++) {
        int min_a = a[i];
        for (int j=i; j>=0; j--) {
            min_a = min(min_a, a[j]);
            if (i-j+1 >= min_a) result = max(result, min_a);
        }
    }
    cout << result << endl;
}
