#include <vector>
#include <iostream>
using namespace std;

struct value {
    int sum, prefix, postfix, res;
};

value combine(const value &u, const value &v) {
    value r;
    r.sum = u.sum + v.sum;
    r.prefix = max(u.prefix, u.sum + v.prefix);
    r.postfix = max(v.postfix, v.sum + u.postfix);
    r.res = max(u.postfix + v.prefix, max(u.res, v.res));
    return r;
}

struct range {
    int l, r;
    bool inside(const range &b) const {
        return b.l<=l && r<=b.r;
    }
    bool intersect(const range &b) const {
        return !(r<b.l || b.r<l);
    }
};

struct node {
    range r;
    value v;
    node *left, *right;
};

node* build_tree(vector<int> &&a) {
    int n = a.size();

    vector<node *> nodes(n);
    for (int i=0; i<n; i++) {
        nodes[i] = new node {{i,i}, {a[i],a[i],a[i],a[i]}, NULL, NULL};
    }

    while (nodes.size() > 1) {
        vector<node *> tmp;
        int n = nodes.size();
        for (int i=1; i<n; i += 2) {
            node *p = new node {
                {nodes[i-1]->r.l, nodes[i]->r.r},
                combine(nodes[i-1]->v, nodes[i]->v),
                nodes[i-1], nodes[i],
            };
            tmp.push_back(p);
        }
        if (n & 1) tmp.push_back(nodes[n-1]);
        swap(nodes, tmp);
    }
    return nodes[0];
}

value query(const node &p, const range &r) {
    if (p.r.inside(r)) return p.v;
    if (!p.left->r.intersect(r)) return query(*p.right, r);
    if (!p.right->r.intersect(r)) return query(*p.left, r);
    return combine(query(*p.left, r), query(*p.right, r));
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    int n; cin >> n;
    vector<int> a(n);
    for (int &x: a) cin >> x;
    node *root = build_tree(move(a));
    int m; cin >> m;
    while (m--) {
        int l, r;
        cin >> l >> r;
        cout << query(*root, {l-1, r-1}).res << '\n';
    }
    return 0;
}
