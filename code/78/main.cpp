#include <vector>
#include <string>
#include <iostream>
#include <cstdio>
using namespace std;

const int BASE = 10000;
typedef vector <int> BigInt;
BigInt Init(string s) {
    BigInt a; if (s.size() == 0) { a.push_back(0); return a; }
    while (s.size() % 4 != 0) s = '0' + s;
    for (int i = 0; i < (int)s.size(); i += 4) {
        int value = 0;
        for (int j = 0; j < 4; j++)
            value = value * 10 + (s[i + j] - '0');
        a.insert(a.begin(), value);
    } return a;
}
void Print(const BigInt a) {
    int L = a.size(); printf("%d", a[L - 1]);
    for (int i = L - 2; i >= 0; i--) printf("%04d", a[i]);
    printf("\n");
}
BigInt operator + (const BigInt a, const BigInt b) {
    BigInt c; int carry = 0;
    for (int i = 0; i < (int)a.size() || i < (int)b.size(); i++) {
        if (i < (int)a.size()) carry += a[i];
        if (i < (int)b.size()) carry += b[i];
        c.push_back(carry % BASE); carry /= BASE;
    }
    if (carry) c.push_back(carry); return c;
}
BigInt operator - (const BigInt a, const BigInt b) {
    BigInt c; int carry = 0;
    for (int i = 0; i < (int)a.size(); i++) {
        int s = a[i] - carry;
        if (i < (int)b.size()) s -= b[i];
        if (s < 0) s += BASE, carry = 1; else carry = 0;
        c.push_back(s);
    }
    while (*c.rbegin() == 0 && c.size() > 1) c.pop_back(); return c;
}
BigInt operator * (const BigInt a, const int mul) {
    BigInt c; int carry = 0;
    for (int i = 0; i < (int)a.size(); i++) {
        carry += a[i] * mul; c.push_back(carry % BASE); carry /= BASE;
    }
    if (carry) c.push_back(carry); return c;
}
BigInt operator * (const BigInt a, const BigInt b) {
    BigInt c(a.size() + b.size() + 5, 0);
    for (int i = 0; i < (int)a.size(); i++) {
        int carry = 0;
        for (int j = 0; j < (int)b.size(); j++) {
            int k = i + j; c[k] += a[i] * b[j] + carry;
            carry = c[k] / BASE; c[k] %= BASE;
        }
        if (carry) c[i + b.size()] += carry;
    }
    while (*c.rbegin() == 0 && c.size() > 1) c.pop_back(); return c;
}
bool operator < (BigInt a, BigInt b) {
    while (a.size() && *a.rbegin() == 0) a.pop_back();
    while (b.size() && *b.rbegin() == 0) b.pop_back();
    if (a.size() != b.size()) return a.size() < b.size();
    for (int i = a.size() - 1; i >= 0; i--)
        if (a[i] != b[i]) return a[i] < b[i];
    return false;
}

int main() {
    string sa, sb;
    cin >> sa >> sb;
    BigInt a = Init(sa);
    BigInt b = Init(sb);
    Print(a + b);
    if (a < b) {
        printf("-");
        Print(b - a);
    } else {
        Print(a - b);
    }
    Print(a * b);
    return 0;
}
