#include <cstdio>
#include <vector>
using namespace std;

// Hàm sinh hoán vị tiếp theo trong thứ tự từ điển.
// Trả về `k` là vị trí mà hoán vị bắt đầu thay
// đổi so với hoán vị trước.
// k < 0 nếu đây đã là hoán vị cuối cùng.
int next(vector<int> &a) {
    int k, l, n = a.size();
    for (k = n-2; k>=0; k--) if (a[k] < a[k+1]) break;
    if (k<0) return k;
    for (l = n-1; l>k; l--) if (a[k] < a[l]) break;
    swap(a[k], a[l]);
    for (int i=k+1, j=n-1; i<j; i++, j--) swap(a[i], a[j]);
    return k;
}

bool f[1000];
int seed = 0;
int cache[1001];

// Kiểm tra xem tại a[i] có thỏa điều kiện L < R
// như đã giải thích ở trên hay không.
bool check(const vector<int> &a, int i) {
    int n = a.size();
    seed += 1;
    int r = 1e9;
    // Tìm R là giá trị nhỏ nhất ở bên phải a[i]
    // Đồng thời đánh dấu các giá trị xuất hiện
    // ở bên phải a[i]
    for (int j=i+1; j<n; j++) {
        cache[a[j]] = seed;
        r = min(r, a[j]);
    }
    // Tìm L là giá trị lớn nhất nhỏ hơn a[i]
    // ở bên trái a[i] => L không xuất hiện ở bên phải
    int l = 0;
    for (int j=a[i]-1; j>=1; j--) {
        if (cache[j] != seed) {
            l = j;
            break;
        }
    }
    return l < r;
}

// Lần lượt kiểm tra và cập nhật các phần tử
// từ a[k] trở lên, đồng thời kiểm tra xem
// tất cả các phần tử có thỏa mãn điều kiện
// L < R hay không.
bool ok(const vector<int> &a, int k) {
    int n = a.size();
    for (int i=k; i<n; i++) {
        f[i] = check(a, i);
        if (i>0) f[i] &= f[i-1];
    }
    return f[n-1];
}

int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    vector<int> a(n);
    for (int i=0; i<n; i++) scanf("%d", &a[i]);

    int k = 0, count = 0;
    while (m--) {
        if (ok(a, k)) count++;
        k = next(a);
        if (k < 0) break;
    }

    printf("%d", count);
    return 0;
}
