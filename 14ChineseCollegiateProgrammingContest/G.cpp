#include <iostream>
#include <vector>
#include <map>
using namespace std;

void Solve() {
    int ile = 0;
    int tury, graczy;
    cin >> tury >> graczy;
    std::map<char, int> owoce;
    std::map<int, pair<char, int>> karty;
    int g = 0;
    while (tury --> 0) {
        char ow; int war;
        cin >> ow >> war;
        if (karty.count(g)) {
            auto b = karty[g];
            owoce[b.first] -= b.second;    
        }
        owoce[ow] += war;
        karty[g] = {ow, war};
        for (auto c : owoce) {
            if (c.second == 5) {
                ile++;
            }
        }

        g = (g + 1) % graczy;
    }
    cout << ile << "\n";
}

int main() {
    ios_base::sync_with_stdio(0);
    int T;
    cin >> T;
    while (T --> 0) {
        Solve();
    }
}