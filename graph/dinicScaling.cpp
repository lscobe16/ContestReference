struct Edge {
	z to, rev, f, c;
};

vector<vector<Edge>> adj; // @\redBox{resize initially!}@
z s, t, flow = 0; // @\redBox{set s and t initially!}@
vz pt, dist;

void addEdge(z u, z v, z cap=1) {
	adj[u].push_back({v, (z)adj[v].size(), 0, cap});
	adj[v].push_back({u, (z)adj[u].size() - 1, 0, 0});
}

bool bfs(z lim) {
	dist = vz(adj.size(), -1);
	dist[s] = 0;
	queue<z> q({s});
	while (!q.empty() && dist[t] < 0) {
		z v = q.front(); q.pop();
		for (Edge& e : adj[v]) {
			if (dist[e.to] < 0 && e.c - e.f >= lim) {
				dist[e.to] = dist[v] + 1;
				q.push(e.to);
	}}}
	return dist[t] >= 0;
}

bool dfs(z v, z flow) {
	if (v == t) return true;
	for (; pt[v] < adj[v].size(); pt[v]++) {
		Edge& e = adj[v][pt[v]];
		if (dist[e.to] != dist[v] + 1) continue;
		if (e.c - e.f >= flow && dfs(e.to, flow)) {
			e.f += flow;
			adj[e.to][e.rev].f -= flow;
			return true;
	}}
	return false;
}

z maxFlow() {
	for (z lim = (1ll << 62); lim >= 1; lim /= 2) {
		while (bfs(lim)) {
			pt = vz(adj.size());
			while (dfs(s, lim)) flow += lim;
	}}
	return flow;
}

// @\yellowBox{decompose}@
vector<pair<vector<Edge*>,int>> paths;
void decompose() { // output in paths
	vz next(adj.size(), 0);
	while(flow > 0) {
		paths.push_back({{}, INF});
		auto& [path, aug] = paths.back();
		vb vis(adj.size(), false);
		while(path.empty() || path.back()->to != t) {
			z v = path.empty() ? s : path.back()->to;
			// not needed if all inner nodes have at most 2 used edges (e.g. unit graph with arbitrary weights)
			if (vis[v]) {
				z cycle_aug = INF;
				z cycle_begin = path.size()-1;
				while (cycle_begin > 0 && path[cycle_begin-1]->to != v) cycle_begin--;
				for(z i=cycle_begin; i<path.size(); ++i)
					cycle_aug = min(cycle_aug, path[i]->f);
				for(z i=cycle_begin; i<path.size(); ++i) {
					path[i]->f -= cycle_aug;
					vis[path[i]->to] = false;
				}
				path.resize(cycle_begin);
			}
			vis[v] = true;
			while (adj[v][next[v]].f <= 0) next[v]++;
			path.push_back(&adj[v][next[v]]);
		}
		fe(e:path) aug = min(aug, e->f);
		flow -= aug;
		fe(e:path) e->f -= aug;
	}
}