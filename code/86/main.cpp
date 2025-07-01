#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

#define u32 unsigned int

struct pack { u32 w, v; };
void operator += (pack &a, const pack &b) {
    a.w += b.w;
    a.v += b.v;
}
bool operator < (const pack &a, const pack &b) {
    return a.w < b.w;
}

// Nhận vào danh sách các khối vàng `a`,
// và trọng lượng tối đa `m`.
// Trả về danh sách tất cả các cách chọn có thể có,
// sắp theo trọng lượng không giảm.
vector<pack> generate(const vector<pack> &a, u32 m) {
    vector<pack> res(1<<a.size());
    int n = 0;

    for (int i=0; i < (int)res.size(); i++) {
        pack tmp = {0, 0};
        for (int k=0; k<(int)a.size(); k++) {
            if (i&(1<<k)) tmp += a[k];
        }
        if (tmp.w <= m) res[n++] = tmp;
    }

    res.resize(n);
    sort(res.begin(), res.end());
    return res;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);

    int n; u32 m;
    cin >> n >> m;

    int n1 = n / 2;
    int n2 = n - n1;

    vector<pack> a(n1), b(n2);
    for (pack &x: a) cin >> x.w >> x.v;
    for (pack &x: b) cin >> x.w >> x.v;

    vector<pack> f(generate(a, m));
    vector<pack> g(generate(b, m));

    u32 result = 0;
    u32 max_value = 0;
    for (int i=f.size()-1, j=0; i>=0; i--) {
        while (j<(int)g.size() && f[i].w + g[j].w <= m) {
            max_value = max(max_value, g[j].v);
            j++;
        }
        result = max(result, max_value + f[i].v);
    }

    cout << result;
    return 0;
}
