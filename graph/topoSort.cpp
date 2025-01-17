vvz adj; // @\redBox{store graph! no yellow -> DAG only!}@
z f, n; // no (re)init necessary
vz fin, topo; // topo: edges go from left to right

void dfs(z u) {
	@\yellow{fin[u] = -1;}@  @\yellowBox{check for acyclicity}@
	fe(v:adj[u]) if (!fin[v]) dfs(v);
		@\yellow{else if (fin[v] == -1) return;}@
	fin[u] = ++f;
}

void@\yellow{bool}@ topoSort() {
	topo = fin = vz(n = adj.size());
	for (z v=f=0; v < n; v++) if (!fin[v]) dfs(v);
	@\yellow{if (f != n) return false;}@
	for (z v = 0; v < n; v++) topo[n-fin[v]] = v;
	@\yellow{return true;}@ // iff adj is DAG iff topo is valid
}
