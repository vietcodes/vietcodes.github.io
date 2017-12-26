#include <iostream>
#include <algorithm>
#include <vector>
#include <tuple>
using namespace std;
#define LL long long
struct pack { int x, y; short index; };
bool operator < (const pack &a, const pack& b) {
    return tie(a.x, a.y) < tie(b.x, b.y);
}
bool operator == (const pack &a, const pack& b) {
    return a.x==b.x && a.y==b.y;
}

int gcd(int a, int b) {
    if (a < 0) a = -a;
    if (b < 0) b = -b;
    int r;
    while (b > 0) r=a%b, a=b, b=r;
    return a;
}

void formalize(pack &a) {
    if (a.y == 0) a.x = 1;
    else if (a.x == 0) a.y = 1;
    else {
        if (a.y < 0) a.y = -a.y, a.x = -a.x;
        int g = gcd(a.x, a.y);
        a.x /= g;
        a.y /= g;
    }
}

bool find(const pack a, const vector<pack> &b) {
    int n = b.size();
    vector<pack> c(n);
    for (int i=0; i<n; i++) {
        c[i].x = b[i].x - a.x;
        c[i].y = b[i].y - a.y;
        c[i].index = b[i].index;
        formalize(c[i]);
    }
    sort(c.begin(), c.end());
    for (int i=1; i<n; i++) {
        if (c[i] == c[i-1]) {
            cout << c[i].index << ' ' << c[i-1].index << ' ' << a.index;
            return true;
        }
    }
    return false;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    int n; cin >> n;
    vector<pack> a(n), b(n);
    for (int i=0; i<n; i++) {
        cin >> a[i].x >> a[i].y;
        a[i].index = i + 1;
    }
    for (int i=0; i<n; i++) {
        cin >> b[i].x >> b[i].y;
        b[i].index = i + 1 + n;
    }
    for (pack p: a) if (find(p, b)) return 0;
    for (pack p: b) if (find(p, a)) return 0;
    cout << -1;
    return 0;
}
