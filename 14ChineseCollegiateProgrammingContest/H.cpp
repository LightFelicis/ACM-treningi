#include <iostream>
#include <vector>
#include <map>
using namespace std;

void Solve() {
    int N;
    cin >> N;
    if (N == 1) {
        cout << 2 << "\n";
        return;
    }
    if (N == 2) {
        cout << 16 << "\n";
        return;
    }
    if (N == 3) {
        cout << 32 << "\n";
    }
    cout << 4 << "\n";
}

int main() {
    ios_base::sync_with_stdio(0);
    int T;
    cin >> T;
    while (T --> 0) {
        Solve();
    }
}