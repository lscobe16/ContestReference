#include "../template/template_compiling.cpp"

template<bool edges>
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

	hld(vvz g, z r = 0) {
		z n = g.size();
		par = in = head = vz(n);
		sz = vz(n, 1);
			dfs(r, r, g);
			decomp(r, r, g);
	}

	z on_path(z u, z v, au f) { //returns lca
		while(1) {
			if(in[v] < in[u]) swap(u, v);
			if(!edges or u!=v) f(max(in[u] + edges, in[head[v]]), in[v] + 1);
			if(in[v = head[v]] <= in[u]) return u;
			v = par[v];
		}
	}

	void on_subtree(z r, au f) {
		if(sz[r] > edges) f(in[r] + edges, in[r] + sz[r]);
	}
};


// lca-Teil tested on: https://judge.yosupo.jp/problem/lca
// with edges=0 and edges=1
int32_t main()
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

	hld<0> hld(G);

	for (z i = 0; i < Q; i++) {
		z a, b;
		cin >> a >> b;
		cout << hld.on_path(a,b,[](z l,z rex){}) << "\n";
	}
}
