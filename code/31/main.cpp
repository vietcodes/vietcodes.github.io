// Bài này chỉ cần duyệt 5 vòng for là AC

#include <iostream>
#include <vector>
using namespace std;
#define LL long long
#define rep(i, a, b) for (int i=a; i<b; i++)

struct pack {int x, y; LL w;};

inline LL calc(LL state, vector<pack>& a) {
    LL res = 0;
    for (auto &x: a) {
        if (state & 1) res += x.w;
        state >>= 1;
    }
    return res;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    int m; cin >> m;
    vector<pack> a(m);
    vector<bool> frei(64, true);
    for (auto &a: a) {
        cin >> a.x >> a.y >> a.w;
        a.x--, a.y--;
        frei[a.x*8+a.y] = false;
    }
    vector<LL> xe(64, 0), tuong(64, 0), ma(64, 0), hau(64, 0);
    int c = 0;
    rep(i, 0, 8) rep(j, 0, 8) if (frei[c]) {
        rep(k, 0, m) {
            int x = a[k].x, y = a[k].y;
            if (x==i || y==j) xe[c] |= 1ll<<k;
            if (x-y==i-j || x+y==i+j) tuong[c] |= 1ll<<k;
            if ((abs(i-x)==2&&abs(j-y)==1) || (abs(i-x)==1&&abs(j-y)==2)) {
                ma[c] |= 1ll<<k;
            }
        }
        hau[c] = xe[c] | tuong[c];
        c++;
    } else c++;

    LL kq = 0;
    rep(h, 0, 64) if (frei[h]) {
        LL s = hau[h];
        frei[h] = false;
        rep(x, 0, 64) if (frei[x]) {
            LL bk = s;
            s |= xe[x];
            frei[x] = false;
            rep(t, 0, 64) if (frei[t]) {
                LL bk = s;
                frei[t] = false;
                s |= tuong[t];
                rep(m, 0, 64) if (frei[m]) {
                    kq = max(kq, calc(s | ma[m], a));
                }
                frei[t] = true;
                s = bk;
            }
            frei[x] = true;
            s = bk;
        }
        frei[h] = true;
    }
    cout << kq << endl;
    return 0;
}
