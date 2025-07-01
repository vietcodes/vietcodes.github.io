#include <cmath>
#include <vector>
#include <iostream>
using namespace std;

struct vec {
    double x, y;
    vec& operator+=(vec v) {
        this->x += v.x, this->y += v.y;
        return *this;
    }
    vec& operator-=(vec v) {
        this->x -= v.x, this->y -= v.y;
        return *this;
    }
    vec& operator*=(double k) {
        this->x *= k, this->y *= k;
        return *this;
    }
    vec& operator/=(double k) {
        this->x /= k, this->y /= k;
        return *this;
    }
};
vec operator+(vec u, vec v) { return u += v; }
vec operator-(vec u, vec v) { return u -= v; }
double operator*(vec u, vec v) { return u.x*v.x + u.y*v.y; }
vec operator*(vec v, double u) { return v *= u; }
vec operator/(vec v, double u) { return v /= u; }
double magnitude(vec u) { return sqrt(u.x*u.x + u.y*u.y); }
double sqr(double d) { return d*d; }

vec gradient(const vector<vec> &a, vec x) {
    vec tmp, res = {0, 0};
    for (auto &u: a) {
        tmp = x - u;
        res += tmp / magnitude(tmp);
    }
    return res;
}

double f(const vector<vec> &a, vec x) {
    double res = 0;
    for (auto& u: a) res += magnitude(x - u);
    return res;
}

double compute(const vector<vec> &a) {
    const double epsilon = 1e-7;
    double gamma = 0.01;
    vec x0, x1 = {0, 0};
    for (auto& u: a) x1 += u;
    x1 /= (double) a.size();
    double f0, f1 = f(a, x1);
    vec g0, g1 = gradient(a, x1);
    do {
        x0 = x1, x1 -= g1 * gamma;
        f0 = f1, f1 = f(a, x1);
        g0 = g1, g1 = gradient(a, x1);
        gamma = (x1 - x0) * (g1 - g0) / sqr(magnitude(g1 - g0));
    } while (abs(f1 - f0) > epsilon);
    return f1;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(0);
    int n; cin >> n;
    vector<vec> a(n);
    for (auto& u: a) cin >> u.x >> u.y;
    cout << compute(a) << "\n";
    return 0;
}
