struct LCA {
	z n, idx=0;
	vz t2n, n2t, dep; // n2t = first time
	SparseTable *st; // Seite @\pageref{sparse}@

	// computes @\greenBox{euler tour}@  in t2n
	void dfs(vvz& G, z u, z p=-1, z d=0) {
		t2n[idx] = u, n2t[u] = idx, dep[idx++] = d;
		for (z v : G[u]) if (v!=p) {
			@\greenBox{u -> v}@  dfs(G, v, u, d+1); @\greenBox{v -> u}@
			t2n[idx] = u, dep[idx++] = d;
	}}
	LCA(vvz& G, z r=0): 
		n(G.size()), dep(2*n), t2n(2*n,-1), n2t(n, 2*n) {
		dfs(G, r);
		@\opt{for (z i = 0; i < g.size(); ++i) if(n2t[i] != 2*n) dfs(G, i);}@
		st = new SparseTable(dep);
	}

	z of(z u, z v) {
		auto [l, r] = minmax(n2t[u], n2t[v]);
		return t2n[st->queryIndex(l, r+1)];
	}
	@\opt{z getDep(z v) {return dep[n2t[v]];}}@
	@\optE{z dist(z u, z v) \{}@
		@\opt{return getDep(u) + getDep(v) - 2*getDep(of(u, v));}@
	@\optE{\}}@
};
