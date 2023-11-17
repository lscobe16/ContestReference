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
	@\opt{for (z v = 0; v < l; v++) for (z u : adj[v])}@
		@\opt{if (pairs[u] < 0) {pairs[u] = v; pairs[v] = u; ans++; break;}}@
	for (z v = 0; v < l; v++) if (pairs[v] < 0) {
		visited = vb(l);
		ans += dfs(v);
	}
	return ans; // Größe des Matchings
}