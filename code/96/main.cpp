#include <iostream>
#include <queue>
using namespace std;

int pop_max(priority_queue<int> &heap) {
    if (heap.empty()) throw 0;
    int top = heap.top();
    while (!heap.empty() && heap.top() == top) heap.pop();
    return top;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    priority_queue<int> heap;
    for (string str; getline(cin, str);) {
        if (str[0] == '+') {
            if (heap.size() < 15000) heap.push(stoi(str));
        } else if (!heap.empty()) {
            pop_max(heap);
        }
    }
    vector<int> res;
    while (!heap.empty()) res.push_back(pop_max(heap));
    cout << res.size() << '\n';
    for (int x: res) cout << x << '\n';
    return 0;
}
