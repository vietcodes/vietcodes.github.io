#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
#define LL long long

struct car {
    int id;
    int a, b;
    double f;
    car(int id, int a, int b): id(id), a(a), b(b) {
        f = (double) a / (double) b;
    }
    bool operator > (const car &b) const {
        return f > b.f;
    }
};

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    int n; cin >> n;
    vector<int> a(n), b(n);
    for (int &x: a) cin >> x;
    for (int &x: b) cin >> x;
    vector<car> cars;
    for (int i=0; i<n; i++) {
        cars.push_back(car(i, a[i], b[i]));
    }
    sort(cars.begin(), cars.end(), greater<car>());

    LL res = 0;
    LL cnt = 0;
    for (car &p: cars) {
        cnt += p.b;
        res += cnt * p.a; 
    }
    cout << res << '\n';
    for (car &p: cars) cout << p.id+1 << ' ';
    return 0;
}
