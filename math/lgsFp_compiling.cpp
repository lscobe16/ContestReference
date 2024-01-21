#include <bits/stdc++.h>
using namespace std;

#define int long long

using z = int;
using vz = vector<z>;
using vvz = vector<vz>;
using vb = vector<bool>;

using pzz = pair<z,z>;
using vpzz = vector<pzz>;
using vvpzz = vector<vpzz>;

using ld = long double;
using vld = vector<ld>;
using vvld = vector<vld>;


#define au auto&&
#define fe(x...) for(au x)

// Usage: z in(n, m)    and    vz inv(a, n)
#define in(x...) x; [](au... a){(cin>>...>>a);}(x);
#define inv(v, n) v(n); fe(_:v){in(_)}

au pr = cout;
au operator-(ostream& o, au t) {return o << t << ' ';}
au operator+(ostream& o, au t) {return o << t << '\n';}
au operator*(ostream& o, au t) {fe (x:t) o-x-""; return o+"";}

z INF = 1e18; //max z = ca. 9e18

#define dbg(x) (cerr<<__LINE__<<": 	"#x" = ")+(x);

#define time(f...) [&](){\
	auto startT = chrono::high_resolution_clock::now(); \
	f; \
	auto stopT = chrono::high_resolution_clock::now(); \
	return chrono::duration_cast<chrono::milliseconds>(stopT - startT).count();}()

z MOD = 998244353;

// a*x + b*y = ggt(a, b)
z extendedEuclid(z a, z b, z& x, z& y) {
	if (a == 0) {x = 0; y = 1; return b;}
	z x1, y1, d = extendedEuclid(b % a, a, x1, y1);
	x = y1 - (b / a) * x1; y = x1;
	return d;
}

z multInv(z n, z p) {
	z x, y;
	extendedEuclid(n, p, x, y); // Implementierung von oben.
	return ((x % p) + p) % p;
}

z gauss(vvz& mat, z mod=MOD) {
	z n = mat.size();
	for (z l = 0; l < n; l++) {
		z j = l;
		while (j < n && mat[j][l] == 0) j++;
		if (j == n) continue;
		swap(mat[l], mat[j]);
		z factor = multInv(mat[l][l], mod);
		for (z& x : mat[l]) x = (x * factor) % mod;
		for (z i = 0; i < n; i++) {
			if (i == l) continue;
			z diff = mat[i][l];
			for (z j = 0; j < mat[0].size(); j++) {
				mat[i][j] -= (diff * mat[l][j]) % mod;
				mat[i][j] = (mat[i][j] + mod) % mod;
	}}}
	for (z i = 0; i < n; i++) { // checks
		bool allZero = true;
		for (z j = i; j < n; j++) allZero &= abs(mat[i][j]) == 0;
		if (allZero && abs(mat[i][n]) != 0) return 0; // no solution
		if (allZero && abs(mat[i][n]) == 0) return 2; // many solutions
	}
    return 1;
}
// invertieren siehe oben

z invert(vvz& A) {
    assert(A.size() == A[0].size());
    z n = A.size();
	vvz AB(n, vz(2*n));
    for (z i = 0; i < n; i++) AB[i][n+i] = 1;
	for (z i = 0; i < n; i++)
		for (z j = 0; j < n; j++) AB[i][j] = A[i][j];
	// assert(gauss(AB) == 1);
	z res = gauss(AB);
	for (z i = 0; i < n; i++)
		for (z j = 0; j < n; j++) A[i][j] = AB[i][n+j];
	return res;
}

// tested on: https://judge.yosupo.jp/problem/inverse_matrix
int32_t main() {
	cin.tie(0)->sync_with_stdio(0);
	cout.precision(16);
	cin.exceptions(cin.failbit); // some WAs ~> RTE
	
	z in(n);
	vvz A(n, vz(n));
	for (z i = 0; i < n; i++) {
		for (z j = 0; j < n; j++) {
			cin >> A[i][j];
		}
	}

	if (invert(A) != 1) {
		cout+"-1";
	} else {
		fe(l:A) cout*l;
	}
}
