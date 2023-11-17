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



vvz adj; // @\redBox{Hier Graph rein speichern}@
vz pairs; // der Partner-Knoten oder -1
vb visited;

bool dfs(z v) {
	if (visited[v]) return false;
	visited[v] = true;
	fe(u : adj[v]) if (pairs[u] < 0 || dfs(pairs[u])) {
		pairs[u] = v; pairs[v] = u; return true;
	}
	return false;
}

z kuhn(z l) { // l = #Knoten links
	pairs = vz(adj.size(), -1);
	z ans = 0;
	// greedy Matching / hot start
	for (z v = 0; v < l; v++) for (z u : adj[v])
		if (pairs[u] < 0) {pairs[u] = v; pairs[v] = u; ans++; break;}
	for (z v = 0; v < l; v++) if (pairs[v] < 0) {
		visited = vb(l);
		ans += dfs(v);
	}
	return ans; // Größe des Matchings
}


// tested on: https://judge.yosupo.jp/problem/bipartitematching
int32_t main() {
	z in(L, R, M);
	
	z N = L + R;
	adj.resize(N);

	for (z i = 0; i < M; i++) {
		z in(a, b);
		adj[a].push_back(b+L);
		adj[b+L].push_back(a);
	}

	z K = kuhn(L);
	cout << K << "\n";

	for (z i = 0; i < L; i++) if (pairs[i] != -1) 
		cout << i << " " << pairs[i]-L << "\n";	
}
