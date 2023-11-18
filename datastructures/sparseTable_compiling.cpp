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

#define in(x...) x; [](au... a){(cin>>a, ...);}(x);
#define inv(v, n) v(n); fe(_:v){in(_)}




struct SparseTable {
	z n; vz a; vvz st;

	// @\orangeBox{config}@  default: min
	z better(z l, z r) { // idempotent, indices!
		return a[l] <= a[r] ? l : r; 
	}
	
	SparseTable(vz &vec): 
		n(vec.size()), a(vec), st(__lg(n)+1, vz(n)) {
		iota(st[0].begin(), st[0].end(), 0);
		for (z j = 0; (2 << j) <= n; j++) {
			for (z i = 0; i + (2 << j) <= n; i++) {
				st[j + 1][i] = better(st[j][i], st[j][i + (1 << j)]);
	}}}

	z queryIndex(z l, z rex) {
		assert(0 <= l && l <= rex && rex <= n); // rex>n => UB
		if (l == rex) return INF; // neutrales Element
		z j = __lg(rex - l);
		return better(st[j][l], st[j][rex - (1 << j)]);
	}
};



// tested on: https://judge.yosupo.jp/problem/staticrmq
int32_t main() {
	z in(N, Q);
	vz inv(A, N);
	SparseTable st(A);

	for (z i = 0; i < Q; i++) {
		z in(l, rex);
		cout << A[st.queryIndex(l, rex)] << "\n";
	}
}
