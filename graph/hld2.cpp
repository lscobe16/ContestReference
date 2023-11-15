struct hld {
	vz par, sz, in, head;
	z i = 0;

	void dfs(z u, z p, vvz &g) {
		par[u] = p;
		fe(v : g[u]) if(v!=p) {
			dfs_sz(v, u, g);
			sz[u] += sz[v];
			au h = g[u][0];
			if (h==p || sz[v]>sz[h]) swap(v, h);
	}}

	void decomp(z u, z h, vvz &g) {
		in[u] = i++;
		head[u] = h;
		fe(v : g[u]) if(v!=par[u])
			dfs_hld(v, v==g[u][0] ? h : v, g);
	}

	// to initialize all vertices/edges in O(n) after construction,
	// call on_path for each vertex/edge
	hld(vvz @\redE{\sout{\&}}@g, z r = 0) {
		z n = g.size();
		par = in = head = vz(n);
		sz = vz(n, 1);
		@\yellowE{for (z r = 0; r < n; ++r) if(!in[r]) \{} \yellowBox{for forest}@
			dfs(r, r, g);
			decomp(r, r, g);
	@\yellowE\}@}

	// u, v inclusive
	// void f(l, rex). Always l < rex. Calls are not ordered!
	// O(log n) calls to f  (=> often time complexity O(log@$^2$@n))
	z on_path(z u, z v, au f) {
		while(1) {
			if(in[v] < in[u]) swap(u, v);
			@\green{if(u!=v)}@ f(max(in[u]@\green{ + 1}@, in[head[v]]), in[v] + 1);
			if(in[v = head[v]] <= in[u]) return u; // returns lca
			v = par[v];
		}
	}

	// void f(l, rex). Always l < rex.
	// 1 call to f  (=> often time complexity O(log n))
	void on_subtree(z r, au f) {
		@\green{if(sz[r]>1)}@ f(in[r]@\green{ + 1}@, in[r] + sz[r]);
	}
}