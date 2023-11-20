#include <bits/stdc++.h>
using namespace std;

#define int long long

using z = int;
using vz = vector<z>;
using vvz = vector<vz>;
using pzz = pair<z, z>;
using vpzz = vector<pzz>;
using vvpzz = vector<vpzz>;
using vb = vector<bool>;
z INF = 1e18;

#define au auto&&
#define fe(x...) for(au x)

#define in(x...) x; [](au... a){((cin>>a), ...);}(x);
#define inv(v, n) v(n); fe(_:v){in(_)}
#define dbg(x) cerr<<__LINE__<<": 	"#x" = "<<(x)<<"\n";

au operator-(ostream& o, au t) {return o << t << ' ';}
au operator+(ostream& o, au t) {return o << t << '\n';}

#define time(f...) [&](){\
	auto startT = chrono::high_resolution_clock::now(); \
	f; \
	auto stopT = chrono::high_resolution_clock::now(); \
	return chrono::duration_cast<chrono::milliseconds>(stopT - startT).count();}()


#include "./scc.cpp"

struct sat2 {
	// insert SCC (@\page{scc}@) here
	z n;
	vz sol;

	sat2(z vars) : n(vars*2) {adj = vvz(n);};

	z pos(z i) {return 2*i;}
	z neg(z i) {return 2*i+1;}
	z dimacs(z x) {return x > 0 ? pos(x-1) : neg(-x-1);}

	void addImpl(z a, z b) {
		adj[a].push_back(b);
		adj[1^b].push_back(1^a);
	}
	void addOr(z a, z b)    {addImpl(1^a, b);}
	void addEquiv(z a, z b) {addImpl(a, b); addImpl(b, a);}
	void addXor(z a, z b)   {addOr(a, b); addOr(1^a, 1^b);}
	void addTrue(z a)       {addImpl(1^a, a);}
	void addFalse(z a)      {addTrue(1^a);}
	void addAnd(z a, z b)   {addTrue(a); addTrue(b);}
	void addNand(z a, z b)  {addOr(1^a, 1^b);}

	bool solvable() {
		scc();
		for (z i = 0; i < n; i += 2) {
			if (idx[i] == idx[i + 1]) return false;
		}
		sol = vz(n, -1);
		for (z i = 0; i < sccCounter; i++) {
			if (sol[sccs[i][0]] == -1) {
				for (z v : sccs[i]) {
					sol[v] = 1;
					sol[1^v] = 0;
		}}}
		return true;
	}
};

// tested on: https://judge.yosupo.jp/problem/two_sat
int32_t main() {
	string _;
	in(_, _);
	z in(n, m);

	sat2 S(n);

	for (z i = 0; i < m; i++) {
		z in(a, b, _);
		S.addOr(S.dimacs(a), S.dimacs(b));
	}

	if (S.solvable()) {
		cout+"s SATISFIABLE"-"v";
		for (z i = 1; i <= n; i++) {
			if (S.sol[S.dimacs(i)]) cout-i;
			else cout-(-i);
		}
		cout-0;
	} else {
		cout+"s UNSATISFIABLE";
	}
}
