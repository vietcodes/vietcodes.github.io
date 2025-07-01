#include <set>
#include <iostream>
using namespace std;

const char *empty = "empty\n";
const char *no = "no\n";

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    typedef set<int>::iterator iter;
    set<int> set;
    while (true) {
        int cmd, x = 0;
        cin >> cmd;

        if (cmd == 0) break;

        if (cmd != 3 && cmd != 4)
            cin >> x;

        // ADD x
        if (cmd == 1) set.insert(x);
        
        // DELETE x
        if (cmd == 2) set.erase(x);

        // MINIMUM
        if (cmd == 3) {
            if (set.empty()) cout << empty;
            else cout << *set.begin() << '\n';
        }

        // MAXIMUM
        if (cmd == 4) {
            if (set.empty()) cout << empty;
            else cout << *set.rbegin() << '\n';
        }

        // SUCC x
        if (cmd == 5) {
            if (set.empty()) cout << empty;
            else {
                iter i = set.upper_bound(x);
                if (i == set.end()) cout << no;
                else cout << *i << '\n';
            }
        }

        // SUCC_2 x
        if (cmd == 6) {
            if (set.empty()) cout << empty;
            else {
                iter i = set.lower_bound(x);
                if (i == set.end()) cout << no;
                else cout << *i << '\n';
            }
        }

        // PRED x
        if (cmd == 7) {
            if (set.empty()) cout << empty;
            else {
                iter i = set.lower_bound(x);
                if (i == set.begin()) cout << no;
                else cout << *(--i) << '\n';
            }
        }

        // PRED_2 x
        if (cmd == 8) {
            if (set.empty()) cout << empty;
            else {
                iter i = set.upper_bound(x);
                if (i == set.begin()) cout << no;
                else cout << *(--i) << '\n';
            }
        }
    }
    return 0;
}
