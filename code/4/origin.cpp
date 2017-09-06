// Problem setter's code

#include <bits/stdc++.h>
#include <stdio.h>
#include <cstdio>
#define pb push_back
#define mp make_pair
#define sz(s) ((int)(s.size()))
#define all(s) s.begin(),s.end()
#define rep(i,a,n) for(int i=a;i<=n;++i)
#define per(i,n,a) for(int i=n;i>=a;--i)
#define dbg(x) cerr << (#x) << " --> " << (x) << nxtl;
#define onlycin ios_base::sync_with_stdio(false); cin.tie(0) 

typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;

using namespace std;

const int MAXN = (int)5e5+228;
const char nxtl = '\n';
const int mod = (int)1e9+7;
const double eps = (double)1e-9;
template<typename T> inline bool updmin(T &a, const T &b) {return a > b ? a = b, 1 : 0;}
template<typename T> inline bool updmax(T &a, const T &b) {return a < b ? a = b, 1 : 0;}
#define y1 qwert
#define y2 trewq
#define x1 asdfg
#define x2 gfdsa
#define left _left
#define right _right

bitset <50005> dp[50005];
bool have[MAXN];
int n, m;
vector < int > g[MAXN], gr[MAXN];
int type[MAXN], from[MAXN], go[MAXN], sz, wh[MAXN];
vector < int > ts;
bool used[MAXN];
vector < int > cmps[MAXN];
vector < pair < int, int > > edge;

void dfs(int x) {
    used[x] = 1;
    for(auto &to : g[x]) if(!used[to])
        dfs(to);
    ts.pb(x);
}
void dfs1(int x) {
    used[x] = 1;
    wh[x] = sz;
    cmps[sz].pb(x);
    for(auto &to : gr[x]) if(!used[to])
        dfs1(to);
}
bool res[MAXN];

int main() {
#ifdef accepted
    freopen(".in", "r", stdin);
    freopen(".out", "w", stdout);
#endif
    onlycin;
    cin >> n >> m;
    rep(i,1,m) {
        int x, y; cin >> x >> y;
        assert(x >= 1 && x <= n);
        assert(y >= 1 && y <= n);
        edge.pb(mp(x,y));
        g[x].pb(y);
        gr[y].pb(x);
    }
    int q; cin >> q;
    rep(i,1,q) {
        cin >> type[i] >> from[i] >> go[i];
        assert(from[i] <= n);
        if(type[i] == 1) {
            n++;
            if(go[i]) {
                edge.pb(mp(n,from[i]));
                g[n].pb(from[i]);
                gr[from[i]].pb(n);
            } else {
                assert(from[i] >= 1 && from[i] <= n);
                edge.pb(mp(from[i],n));
                g[from[i]].pb(n);
                gr[n].pb(from[i]);
            }
        } else assert(go[i] >= 1 && go[i] <= n);
    }
    assert(n <= 50000);
    rep(i,1,n) if(!used[i]) dfs(i);
    reverse(all(ts));
    memset(used,0,sizeof used);
    for(auto &to : ts) {
        if(!used[to]) {
            sz++;
            dfs1(to);
        }
    }
    rep(i,1,n) g[i].clear();
    for(auto &to : edge) {
        if(wh[to.first] != wh[to.second]) g[wh[to.first]].pb(wh[to.second]);
    }
    memset(used,0,sizeof used);
    rep(i,1,sz) {
        if(!used[i]) {
            dfs(i);
        }
    }
    for(auto &to : ts) {
        dp[to].set(to,1);
        for(auto &it : g[to]) dp[to] |= dp[it];
    }
    per(i,q,1) {
        if(type[i] == 1) {
            n--;
        } else {
            if(go[i] > n || from[i] > n) continue;
            res[i] = dp[wh[from[i]]].test(wh[go[i]]);
        }
    }
    rep(i,1,q) {
        if(type[i] == 1) continue;
        if(res[i]) cout << "Yes\n";
        else cout << "No\n";
    }

    return 0;
}
