struct hld {
	vz par, sz, in, head;
	z i = 0;

	void dfs(z u, z p, vvz &g) {
		par[u] = p;
		fe(v : g[u]) if(v!=p) {
			dfs(v, u, g);
			sz[u] += sz[v];
			au h = g[u][0];
			if (h==p || sz[v]>sz[h]) swap(v, h);
	}}

	void decomp(z u, z h, vvz &g) {
		in[u] = i++;
		head[u] = h;
		fe(v : g[u]) if(v!=par[u])
			decomp(v, v==g[u][0] ? h : v, g);
	}

	hld(vvz @\redE{\sout{\&}}@g, z r = 0) {
		z n = g.size();
		par = in = head = vz(n);
		sz = vz(n, 1);
		@\yellowE{for (z r = 0; r < n; ++r) if(!in[r]) \{} \yellowBox{for forest}@
			dfs(r, r, g);
			decomp(r, r, g);
	@\yellowE\}@}

	z on_path(z u, z v, au f) { @\grayBox{returns lca}@
		while(1) {
			if(in[v] < in[u]) swap(u, v);
			@\green{if(u!=v)}@ f(max(in[u]@\green{ + 1}@, in[head[v]]), in[v] + 1);
			if(in[v = head[v]] <= in[u]) return u;
			v = par[v];
		}
	}

	void on_subtree(z r, au f) { @\optAnn@
		@\green{if(sz[r]>1)}@ f(in[r]@\green{ + 1}@, in[r] + sz[r]);
	}
}