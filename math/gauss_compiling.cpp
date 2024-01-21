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

z INF = 1e18; //max z = ca. 9e18

#define dbg(x) (cerr<<__LINE__<<": 	"#x" = ")+(x);

#define time(f...) [&](){\
    auto startT = chrono::high_resolution_clock::now(); \
    f; \
    auto stopT = chrono::high_resolution_clock::now(); \
    return chrono::duration_cast<chrono::milliseconds>(stopT - startT).count();}()

ld EPS = 1e-6;

z gauss(vvld& mat) {
    z n = mat.size();
	vb done(n, false);
	for (z l = 0; l < n; l++) {
		z swappee = l; // more stability
		for (z j = 0; j < n; j++) {
			if (done[j]) continue;
			if (abs(mat[j][l]) > abs(mat[l][l])) swappee = j;
		}
		swap(mat[l], mat[swappee]);
		if (abs(mat[l][l]) > EPS) {
            ld factor = mat[l][l];
            for (ld& x : mat[l]) x /= factor;
            for (z i = 0; i < n; i++) {
                if (i == l) continue;
                ld diff = mat[i][l];
                for (z j = 0; j < mat[0].size(); j++) {
                    mat[i][j] -= diff * mat[l][j];
            }}
			done[l] = true;
	}}
	for (z i = 0; i < n; i++) { // checks
		bool allZero = true;
		for (z j = i; j < n; j++) allZero &= abs(mat[i][j]) <= EPS;
		if (allZero && abs(mat[i][n]) > EPS) return 0; // no solution
		if (allZero && abs(mat[i][n]) <= EPS) return 2; // many solutions
	}
    return 1;
}

void invert(vvld& A) {
    assert(A.size() == A[0].size());
    z n = A.size();
	vvld AB(n, vld(2*n));
    for (z i = 0; i < n; i++) AB[i][n+i] = 1;
	for (z i = 0; i < n; i++)
		for (z j = 0; j < n; j++) AB[i][j] = A[i][j];
	assert(gauss(AB) == 1);
	for (z i = 0; i < n; i++)
		for (z j = 0; j < n; j++) A[i][j] = AB[i][n+j];
}

// invert tested on: https://codeforces.com/gym/104670/problem/F
