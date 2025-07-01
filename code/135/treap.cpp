#include <iostream>
using namespace std;
#define LL long long
 
struct TreapNode {
    LL key;
    int prio, cnt = 1;
    TreapNode *left = NULL, *right = NULL;
    TreapNode(LL key): key(key), prio(rand()) {}
};

int get_cnt(TreapNode *p) {
    return p? p->cnt : 0;
}

TreapNode* rightRotate(TreapNode *y) {
    TreapNode *x = y->left, *T2 = x->right;
    x->right = y;
    y->left = T2;
    int temp = y->cnt;
    y->cnt = y->cnt - x->cnt + get_cnt(T2);
    x->cnt = temp;
    return x;
}
 
TreapNode* leftRotate(TreapNode *x) {
    TreapNode *y = x->right, *T2 = y->left;
    y->left = x;
    x->right = T2;
    int temp = x->cnt;
    x->cnt = x->cnt - y->cnt + get_cnt(T2);
    y->cnt = temp;
    return y;
}
 
TreapNode* insert(TreapNode* root, LL key) {
    if (!root) return new TreapNode(key);
    root->cnt += 1;
    if (key < root->key) {
        root->left = insert(root->left, key);
        if (root->left->prio > root->prio) root = rightRotate(root);
    } else if (key > root->key) {
        root->right = insert(root->right, key);
        if (root->right->prio > root->prio) root = leftRotate(root);
    }
    return root;
}
 
int count_less(TreapNode* root, LL key) {
    if (!root) return 0;
    if (key == root->key) return get_cnt(root->left);
    if (key < root->key) return count_less(root->left, key);
    return root->cnt - get_cnt(root->right) + count_less(root->right, key);
}

int main() {
    srand(time(NULL));
    ios::sync_with_stdio(false); cin.tie(0);
    int n; cin >> n;
    LL l, r; cin >> l >> r;
    LL sum = 0, res = 0;
    TreapNode* root = NULL;
    root = insert(root, sum);
    while (n--) {
        int x; cin >> x;
        sum += x;
        res += count_less(root, sum - l + 1) - count_less(root, sum - r);
        root = insert(root, sum);
    }
    cout << res;
    return 0;
}
