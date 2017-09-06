#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

//Ta sắp xếp các điểm đen và điểm trắng theo toạ độ
//rồi chọn các cặp đen trắng kề nhau

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    struct pack {int val, color;};
    int n; cin >> n;
    vector<pack> a(2*n);
    for (int i=0; i<n; i++) {
        cin >> a[i].val;
        a[i].color = 0;
    }
    for (int i=n; i<2*n; i++) {
        cin >> a[i].val;
        a[i].color = 1;
    }
    sort(a.begin(), a.end(), [](pack &a, pack &b){return a.val < b.val;} );
    int res = 0;
    for (int i=1; i<2*n; i++) if (a[i].color != a[i-1].color) {
        res++;
        i++;
    }
    cout << res;
    return 0;
}
