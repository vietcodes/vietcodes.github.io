#include <cmath>
#include <iostream>
using namespace std;

#define rep(i, a, b) for(int i=a; i<b; i++)

const int S = 18;
const int N = 1<<S;

struct complex {
    double r, i;
    complex(): r(0), i(0) {}
    complex(double t): r(cos(t)), i(sin(t)) {}
    complex(double r, double i): r(r), i(i) {}
    void operator/=(double d) {
        this->r /= d;
        this->i /= d;
    }
};
complex operator+(complex a, complex b) {
    a.r += b.r;
    a.i += b.i;
    return a;
}
complex operator-(complex a, complex b) {
    a.r -= b.r;
    a.i -= b.i;
    return a;
}
complex operator*(complex a, complex b) {
    return complex(a.r*b.r - a.i*b.i, a.r*b.i + a.i*b.r);
}

int reverse(int n) {
    int r = 0;
    rep(i, 0, S) r |= ((n & (1<<i))>>i)<<(S - i - 1);
    return r;
}

complex* fft(complex *a, bool inv=false) {
    complex *b = new complex[N];
    rep(i, 0, N) b[i] = a[reverse(i)];
    rep(s, 0, S) {
        int len = 1 << s;
        complex w((inv? 1:-1) * M_PI / len);
        int i = 0, j = 0;
        for (int count = N >> (s + 1); count--;) {
            i = j;
            j = i + len;
            complex t(1.0, 0);
            for (int l=len; l--;) {
                a[i] = b[i] + t*b[j];
                a[j] = b[i] - t*b[j];
                t = t * w;
                i++, j++;
            }
        }
        swap(a, b);
    }
    delete[] a;
    if (inv)  rep(i,0,N) b[i] /= N;
    return b;
}

template<class T> T read() {
    T t; cin >> t; return t;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    int m = read<int>();
    complex *a = new complex[N];
    complex *b = new complex[N];
    rep(i,0,m) a[read<int>() + 50000].r += 1.0;
    rep(i,0,m) b[read<int>() + 50000].r += 1.0;
    a = fft(a);
    b = fft(b);
    rep(i,0,N) a[i] = a[i] * b[i];
    a = fft(a, true);
    long long kq = 0;
    rep(i,0,m) kq += round(a[read<int>() + 100000].r);
    cout << kq;
    delete[] a;
    delete[] b;
    return 0;
}
