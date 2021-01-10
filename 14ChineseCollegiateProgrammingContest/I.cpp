#include <iostream>
#include <vector>
#include <map>
using namespace std;

void Solve(int N) {
    int x;
    int wynik = 0;
    vector <vector <int> > V(N, vector<int>(N));
    int mini_niezero = 123456789;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cin >> V[i][j];
            if (V[i][j] != 0) {
                mini_niezero = min(mini_niezero, V[i][j]);
            }
        }
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            wynik += (V[i][j] == mini_niezero);
        }
    }
    cout << wynik / 2 << "\n";
}

int main() {
    ios_base::sync_with_stdio(0);
    int N;
    while (cin >> N) {
        Solve(N);
    }
}