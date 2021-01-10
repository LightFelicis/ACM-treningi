#include <iostream>
#include <algorithm>
#include <set>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

using ll	= long long;
using ull	= unsigned long long;
using ld	= long double;
using pii	= pair<int,int>;
using pll	= pair<ll,ll>;
using vi	= vector<int>;
using vb	= vector<bool>;
using vc	= vector<char>;
using vvc	= vector<vc>;
using vvi	= vector<vi>;
using vvb	= vector<vb>;
using vpii	= vector<pii>;
using vpll	= vector<pll>;
using vll	= vector<ll>;
using vvll	= vector<vll>;
using vull	= vector<ull>;
#define f first
#define s second
#define pb emplace_back
#define rep(i, begin, end) for(auto i = (begin); i <= (end); ++i)
#define repr(i, begin, end) for(auto i = (begin); i >= (end); --i)
#define bend(X) X.begin(), X.end()
#ifdef LOCAL
#define nl << endl
#define deb(x) cout << #x << " = " << x << endl
#define say(x) cout << x << endl
#else
#define nl << '\n'
#define deb(x)
#define say(x)
#endif
constexpr int INF = 1e9+1e7;
constexpr ll INFl = INF;
constexpr ll INFll = 1e18+1e16;
void print() { cout << '\n'; }
template <typename T, typename... Args> void print(T x, Args... args) { cout << x << ' '; print(args...); }
template <typename T1, typename T2> ostream& operator<<(ostream& os, pair<T1,T2> x) { os << '(' << x.f << ' ' << x.s << ')'; return os; }
template <typename T1, typename T2> istream& operator>>(istream& is, pair<T1,T2>& x) { is >> x.f >> x.s; return is; }
template <typename T> ostream& operator<<(ostream& os, vector<T>& x) { for(T& i : x) os << i << ' '; return os; }
template <typename T> istream& operator>>(istream& is, vector<T>& x) { for(T& i : x) is >> i; return is; }
template <typename T1, typename T2> pair<T1,T2> operator+(const pair<T1,T2>& A, const pair<T1,T2>& B) { return {A.f+B.f, A.s+B.s}; }
template <typename T1, typename T2> pair<T1,T2> operator-(const pair<T1,T2>& A, const pair<T1,T2>& B) { return {A.f-B.f, A.s-B.s}; }
template <typename T1, typename T2> pair<T1,T2> operator-(const pair<T1,T2>& A) { return {-A.f, -A.s}; }
template <typename T1, typename T2> bool maxe(T1& A, const T2& B) { if(B>A) { A=B; return 1; } return 0; }
template <typename T1, typename T2> bool mine(T1& A, const T2& B) { if(B<A) { A=B; return 1; } return 0; }
 
//////////////////////////////////////////////////
 
string S;
vector<pair<char,int>> T;
 
char cyfra(int x) {
	if(x < 10) return '0'+x;
	return 'A'+x-10;
}
string hex(int x) {
	string R = "";
	while(x > 0) {
		R = cyfra(x%16)+R;
		x /= 16;
	}
	return R;
}

string kompresuj(string d) {
    T.clear();
    string p = "";
	for(auto x : d) {
        if (x == '#') {
            T.pb(x, 0);
        }
		if(T.size() > 0 && x == T.back().f)
			T.back().s++;
		else
			T.pb(x,1);
	}

    for (auto ps : T) {
        if (ps.first == '#') {
            continue;
        }
        if (ps.second == 1) {
            p += ps.first;
            continue;
        }
        p += ps.first + hex(ps.second);
    }

    return p;
}
 
ll solve() {
    vector <pair<int, string>> wynik;
    for (int i = 0; i < S.size(); i++) {
        string subs = S.substr(0, i) + '#' + S.substr(i + 1, S.size() - i - 1);
        auto x = kompresuj(subs);
        wynik.push_back({x.size(), x});
    }
    sort(wynik.begin(), wynik.end());
    cout << wynik[0].second << endl;	
	return -INF;
}
 
void in() {
	T.clear();
}
 
 
 
int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int noOfTests = 1;
	//cin >> noOfTests;
	
	while(cin >> S) {
		in();
		ll result = solve();
		if     (result == ll(-'t')) cout << "TAK\n";
		else if(result == ll(-'n')) cout << "NIE\n";
		else if(result == ll(-'y')) cout << "YES\n";
		else if(result == ll(-'o')) cout << "NO\n";
		else if(result == ll(-'e')) cout << "Popsute\n";
		else if(result != -INF) cout << result << '\n';
	}
	
	return 0;
}
 