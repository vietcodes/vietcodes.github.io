#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    int n; cin >> n;
    vector<int> a(n);
    for (int &x: a) cin >> x;
    
    vector<int> stack;
    vector<int> l(n);
    for (int i=0; i<n; i++) {
        while (!stack.empty() && a[stack.back()] >= a[i]) {
            stack.pop_back();
        }
        l[i] = stack.empty()? 0 : stack.back()+1;
        stack.push_back(i);
    }

    stack.clear();
    vector<int> r(n);
    for (int i=n-1; i>=0; i--) {
        while (!stack.empty() && a[stack.back()] >= a[i]) {
            stack.pop_back();
        }
        r[i] = stack.empty()? n-1 : stack.back()-1;
        stack.push_back(i);
    }

    int result = 1;
    for (int i=0; i<n; i++) {
        if (a[i] <= r[i] - l[i] + 1) {
            result = max(result, a[i]);
        }
    }
    cout << result << endl;
}
