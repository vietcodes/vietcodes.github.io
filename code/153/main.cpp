#include <iostream>
#include <vector>
using namespace std;

int main() {
    int s1, s2, s3;
    cin >> s1 >> s2 >> s3;
    vector<int> count(s1 + s2 + s3 + 1);
    for (int i = 1; i <= s1; i++) {
        for (int j = 1; j <= s2; j++) {
            for (int k = 1; k <= s3; k++) {
                count[i+j+k] += 1;
            }
        }
    }
    int res = 1;
    for (int i=2; i<(int)count.size(); i++) {
        if (count[i] > count[res]) res = i;
    }
    cout << res << endl;
}
