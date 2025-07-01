#include <iostream>
using namespace std;

struct interval {
    int l, r;
    bool inside(interval b) {
        return b.l<=l && r<=b.r;
    }
    bool intersect(interval b) {
        return !(r<b.l || b.r<l);
    }
    int mid() {
        return l + (r-l) / 2;
    }
};

struct node {
    interval range;
    node *left, *right;
    int value, lazy;
    node(interval range): range(range), left(nullptr), right(nullptr), value(0), lazy(0) {}
    ~node() { delete left; delete right; }
    void lazy_down() {
        if (!left) {
            int mid = range.mid();
            left = new node({range.l, mid});
            right = new node({mid+1, range.r});
        }
        left->value += lazy;
        left->lazy += lazy;
        right->value += lazy;
        right->lazy += lazy;
        lazy = 0;
    }
    void update(interval r, int val) {
        if (!range.intersect(r)) return;
        if (range.inside(r)) value += val, lazy += val;
        else {
            lazy_down();
            left->update(r, val);
            right->update(r, val);
            value = max(left->value, right->value);
        }
    }
    int get_max(interval r) {
        if (!range.intersect(r)) return 0;
        if (range.inside(r)) return value;
        lazy_down();
        return max(left->get_max(r), right->get_max(r));
    }
};

int read() { int t; cin >> t; return t; }

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    node node({1, read()});
    for (int m = read(); m--;) {
        int l, r, v; cin >> l >> r >> v;
        node.update({l, r}, v);
    }
    for (int m = read(); m--;) {
        int l, r; cin >> l >> r;
        cout << node.get_max({l, r}) << '\n';
    }
    return 0;
}
