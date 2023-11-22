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

vvz adj; // @\redBox{store graph! no yellow -> DAG only!}@
z f = 1, n;
vz fin, topo; // topo: edges go left to right

void dfs(z u) {
	// fin[u] = -1;
	fe(v:adj[u]) if (!fin[v]) dfs(v);
		// else if (fin[v] == -1) return;
	fin[u] = f++;
}

bool topoSort() {
	topo = fin = vz(n = adj.size());
	for (z v = 0; v < n; v++) if (!fin[v]) dfs(v);
	// if (f != n+1) return false;
	for (z v = 0; v < n; v++) topo[n-fin[v]] = v;
	// return true; // iff adj is DAG iff topo is valid
}


// tested
int32_t main() {
	z in(n, m);
	adj.resize(n);
	for (z i = 0; i < m; i++) {
		z in(a, b);
		adj[a].push_back(b);
	}

	if (topoSort()) {
		fe(x:topo) cout-x;
		cout+"";
	} else {
		cout+"not acyclic!";
	}
}

/* test inputs:
3 3
0 1
1 2
2 0

4 4
0 1
0 2
1 3
2 3

4 0
*/
