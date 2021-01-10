#include <iostream>
#include <vector>
#include <map>
using namespace std;

/*
0000000111
0000001011
0000001101
0000001110
0000010011
000001xxxx
*/



void Solve() {
    int N, K;
    cin >> N >> K;
    if (N == 1) {
        cout << 1 << "\n";
        return;
    }
    if (K == N || (K % 2 == 0)) {
        cout << -1 << "\n";
        return;
    }
    vector <unsigned long long> tab;
    unsigned long long rzad = (1ll << (K + 1ll)) - 1ll;
    for (long long i = K; i >= 0; i--) {
        tab.push_back(rzad ^ (1ll << i));
    }
    unsigned long long rzad2 = (1ll << (K - 1ll)) - 1ll;
    for (long long i = K + 1ll; i < N; i++) {
        tab.push_back(rzad2 ^ (1ll << i));
    }
 
    for (auto c : tab) {
        cout << c << " ";
    }
    cout << "\n";
}
 
int main() {
    ios_base::sync_with_stdio(0);
    int T;
    cin >> T;
    while (T --> 0) {
        Solve();
    }
}