vvz adj, sccs;
z counter, sccCounter;
vb inStack;
vz low, idx, S; // idx: v -> scc(v)  @\red{or -1, if v in none}@

void visit(z v) {
	z old = low[v] = counter++;
	S.push_back(v); inStack[v] = true;

	for (auto u : adj[v]) {
		if (low[u] < 0) visit(u);
		if (inStack[u]) low[v] = min(low[v], low[u]);
	}

	if (old == low[v]) {
		sccs.push_back({});
		z u;
		do {
			u = S.back(); S.pop_back(); inStack[u] = false;
			idx[u] = sccCounter;
			sccs[sccCounter].push_back(u);
		} while (u != v);
		sccCounter++;
}}

void scc() {
	z n = adj.size();
	inStack = vb(n);
	low = vz(n, -1);
	idx = vz(n, -1);
	sccs.clear();

	counter = sccCounter = 0;
	for (z i = 0; i < n; i++) {
		if (low[i] < 0) visit(i);
}}
