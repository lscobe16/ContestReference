vvz adj, sccs;
z counter;
vb inStack;
vz low, idx, S; // idx: v -> scc(v)  @\redBox{or -1, if v in none}@

void visit(z v) {
	z old = low[v] = counter++;
	S.push_back(v); inStack[v] = true;

	for (auto u : adj[v]) {
		if (low[u] < 0) visit(u);
		if (inStack[u]) low[v] = min(low[v], low[u]);
	}

	if (old == low[v]) {
		sccs.push_back({});
		for (z u = -1; u != v;) {
			u = S.back(); S.pop_back(); inStack[u] = false;
			idx[u] = sccs.size() - 1;
			sccs.back().push_back(u);
}}}

void scc() {
	z n = adj.size();
	inStack = vb(n);
	low = vz(n, -1);
	idx = vz(n, -1);
	sccs.clear();

	counter = 0;
	for (int i = 0; i < sz(adj); i++) {
		if (low[i] < 0) visit(i);
}}
