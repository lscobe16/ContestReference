#include <bits/stdc++.h>
using namespace std;

using z = long long;
using vz = vector<z>;
using vvz = vector<vz>;
z INF = 1e18;

#include "../datastructures/sparseTable.cpp"

struct LCA {
    z n, idx=0;
	vz t2n, n2t, dep; // n2t = first time
	SparseTable *st; // -> 1.5

    // computes @\greenBox{euler tour}@
	void dfs(vvz& G, z u, z p=-1, z d=0) {
		t2n[idx] = u, n2t[u] = idx, dep[idx++] = d;
		for (z v : G[u]) if (v!=p) {
				dfs(G, v, u, d+1);
				t2n[idx] = u, dep[idx++] = d;
			}}
	LCA(vvz& G, z r=0): n(G.size()), dep(2*n), t2n(2*n,-1), n2t(n, 2*n) {
		dfs(G, r);
		st = new SparseTable(dep);
	}

	z of(z u, z v) {
		auto [l, r] = minmax(n2t[u], n2t[v]);
		return t2n[st->queryIndex(l, r+1)];
	}
};


// tested on: https://judge.yosupo.jp/problem/lca
int main(int argc, char const *argv[])
{
    z N, Q;
    cin >> N >> Q;
    vvz G(N);


    for (z i = 1; i < N; i++) {
        z p;
        cin >> p;
        G[p].push_back(i);
        G[i].push_back(p);
    }

    LCA lca(G);

    for (z i = 0; i < Q; i++) {
        z a, b;
        cin >> a >> b;
        cout << lca.of(a, b) << "\n";
    }
}
