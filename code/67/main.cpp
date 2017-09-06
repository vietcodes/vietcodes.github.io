#include <iostream>
#include <string> 
#include <sstream> 
#include <vector> 
#include <cmath> 
using namespace std;

#define LL long long

bool is_prime(LL x) {
    if (x == 0) return false;
    for (LL i=2; i*i<=x; i++) if (x % i == 0) return false;
    return true;
}

LL sqrt(LL x) {
    return round(pow(x, 0.5));
}

LL cbrt(LL x) {
    return round(pow(x, 1.0/3.0));
}

bool is_special(LL x) {
    LL r = sqrt(x);
    LL r3 = cbrt(x);
    return r*r == x || (r3*r3*r3 == x && is_prime(r3));
}

vector<LL> read(string &&s) {
    vector<LL> a;
    a.push_back(0);
    stringstream ss(s);
    for (LL x; ss >> x;) {
        if (is_special(x)) a.push_back(x);
    }
    return a;
}

int f[1001][1001];

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    string sa;
    getline(cin, sa);
    vector<LL> a = read(move(sa));

    string sb;
    getline(cin, sb);
    vector<LL> b = read(move(sb));

    int m = a.size()-1, n = b.size()-1;

    for (int i=1; i<=m; i++) for (int j=1; j<=n; j++) {
        if (a[i] == b[j]) f[i][j] = f[i-1][j-1] + 1;
        else f[i][j] = max(f[i-1][j], f[i][j-1]);
    }

    cout << f[m][n];
    return 0;
}
