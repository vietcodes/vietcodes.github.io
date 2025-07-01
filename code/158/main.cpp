#include <iostream>
using namespace std;

unsigned char *pool;
size_t pool_top = 0;

struct Interval {
    int l, r;
    bool inside(Interval b) { return b.l <= l && r <= b.r; }
    bool intersect(Interval b) { return !(r < b.l || b.r < l); }
    int mid() { return l + (r - l) / 2; }
};

struct Node {
    Interval range;
    Node *left, *right;
    int value, lazy;

    void lazy_down() {
        if (!left) {
            int mid = range.mid();
            left = new Node({range.l, mid});
            right = new Node({mid + 1, range.r});
        }
        left->value += lazy;
        left->lazy += lazy;
        right->value += lazy;
        right->lazy += lazy;
        lazy = 0;
    }

    static void *operator new(std::size_t count) {
        void *p = pool + pool_top;
        pool_top += count;
        return p;
    }

   public:
    Node(Interval range)
        : range(range), left(nullptr), right(nullptr), value(0), lazy(0) {}

    void update(Interval r, int val) {
        if (!range.intersect(r)) return;
        if (range.inside(r)) {
            value += val;
            lazy += val;
        } else {
            lazy_down();
            left->update(r, val);
            right->update(r, val);
            value = max(left->value, right->value);
        }
    }

    int get_max(Interval r) {
        if (!range.intersect(r)) return 0;
        if (range.inside(r)) return value;
        lazy_down();
        return max(left->get_max(r), right->get_max(r));
    }
};

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);
    int N, K, M;
    cin >> N >> K >> M;
    pool = new unsigned char[N * 4 * sizeof(Node)];
    Node tree({0, N - 1});
    while (M--) {
        int l, r;
        cin >> l >> r;
        r -= 1;
        if (tree.get_max({l, r}) < K) {
            cout << "1\n";
            tree.update({l, r}, 1);
        } else {
            cout << "0\n";
        }
    }
    delete[] pool;
}
