#include <iostream>
#include <utility>
#include <vector>
#include <algorithm>
using namespace std;
#define LL long long

// Tính diện tích hình với `n` là số đỉnh và `x`, `y` là tọa độ các đỉnh.
//
// Ta không nhân với 1/2 như công thức ở trên nên
// kết quả trả về là 2 lần diện tích hình cần tính.
LL S(int n, const vector<LL> &x, const vector<LL> &y) {
    LL s = 0;
    for (int i=0; i<n; i++) s += (x[i]-x[(i+1)%n])*(y[i]+y[(i+1)%n]);
    return s>0?s:-s;
}

int f[1000];

// Tìm thửa ruộng lớn nhất với `k` có ý nghĩa như trong đề,
// `c` là màu được chọn, các thửa ruộng có màu khác sẽ phải
// chuyển về `c`.
// `a` là mảng mô tả các thử ruộng với `first` là diện tích
// thửa ruộng, `second` là màu của thửa ruộng.
LL process(const vector< pair<LL, int> > &a, int k, int c) {
    int m = a.size();

    // Mảng f có ý nghĩa:
    // f[i] là số thửa ruộng cần đổi màu để chuyển 
    // tất cả các thử ruộng từ 0 đến i về màu c.
    f[0] = a[0].second != c;
    for (int i=1; i<m; i++) {
        f[i] = f[i-1] + (a[i].second != c);
    }

    // duyệt dùng 2 con trỏ l và r.
    LL sum = 0, res = 0;
    for (int r=0, l=0; r<m; r++) {
        sum += a[r].first;
        while (f[r] - (l==0?0:f[l-1]) > k) {
            sum -= a[l].first;
            l += 1;
        }
        res = max(res, sum);
    }
    return res;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);

    int m, k; cin >> m >> k;
    vector< pair<LL, int> > a(m);
    for (int i=0; i<m; i++) {
        int n, c; cin >> n >> c;
        vector<LL> x(n), y(n);
        for (int j=0; j<n; j++) cin >> x[j] >> y[j]; 
        a[i] = make_pair(S(n, x, y), c);
    }

    sort(a.begin(), a.end());
    for (int i=m-1; i>0; i--) {
        a[i].first -= a[i-1].first;
    }

    LL res = 0;
    for (int c=1; c<=m; c++) {
        res = max(res, process(a, k, c));
    }

    // Vì kết quả tính được là 2 lần diện tích
    // nên ta thực hiện chia 2 như bên dưới để
    // tránh sử dụng số thực.
    if (res%2 == 1) cout << res/2 << ".5";
    else cout << res/2 << ".0";

    return 0;
}
