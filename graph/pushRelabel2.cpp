struct Edge {
	z from, to, f, c;
};

vector<Edge> edges;
vvz adj, hs; // @\redBox{resize adj!}@
vz ec, cur, H; 

void addEdge(z from, z to, z c) {
	adj[from].push_back(edges.size());
	edges.push_back({from, to, 0LL, c});
	adj[to].push_back(edges.size());
	edges.push_back({to, from, 0, 0});
}

void push(z id, z f) {
	if (ec[edges[id].to] == 0 && f > 0)
		hs[H[edges[id].to]].push_back(edges[id].to);
	edges[id].f += f;
	edges[id^1].f -= f;
	ec[edges[id].to] += f;
	ec[edges[id].from] -= f;
}

z maxFlow(z s, z t) {
	z n = adj.size();
	hs = vvz(2*n);
	ec = cur = H = vz(n);
	H[s] = n;
	ec[t] = 1; // trick: never set t to active
	vz co(2*n);
	co[0] = n - 1;
	for (z id : adj[s]) push(id, edges[id].c);
	for (z hi = 0;;) {
		while (hs[hi].empty()) if (!hi--) return -ec[s];
		z v = hs[hi].back(); hs[hi].pop_back();
		while (ec[v] > 0) {
			if (cur[v] == adj[v].size()) {
				H[v] = 2*n;
				for (z i = 0; i < adj[v].size(); i++) {
					auto [_, to, f, c] = edges[adj[v][i]];
					if (c - f > 0 && H[v] > H[to] + 1) {
						H[v] = H[to] + 1;
						cur[v] = i;
				}}
				co[H[v]]++;
				if (!--co[hi] && hi < n) {
					for (z u = 0; u < n; u++) {
						if (hi < H[u] && H[u] < n) {
							co[H[u]]--;
							H[u] = n + 1;
				}}}
				hi = H[v];
			} else {
				auto [_, to, f, c] = edges[adj[v][cur[v]]];
				if (c - f > 0 && H[v] == H[to] + 1) {
					push(adj[v][cur[v]], min(ec[v], c - f));
				} else {
					cur[v]++;
}}}}}
