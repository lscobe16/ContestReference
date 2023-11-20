// adj[i] = {(j, c(e)) | (i, j) = e in E}
using pzz = pair<z, z>; //dist, destination
@\green{pair<}@vz@\green{, vz>}@ dijkstra(vvpzz& adj, z start) {
	priority_queue<pzz, vpzz, greater<pzz>> Q;
	vz dist(adj.size(), INF)@\green{, prev(adj.size(), -1)}@;
	dist[start] = 0; Q.emplace(0, start);

	while (Q.size()) {
		auto [du, u] = Q.top(); Q.pop();
		if (du > dist[u]) continue; // lazy decreaseKey
		fe([v, c] : adj[u]) {
			if (du + c < dist[v]) {
				dist[v] = du + c;
				@\green{prev[v] = u;}@
				Q.emplace(dist[v], v);
	}}}
	return @\greenE{\{}@dist@\greenE{, prev\}}@;
}

@\green{vz path = {{t}}; z c = t;}@
@\green{while (c != s) path.push_back(c = prev[c]);}@
@\green{reverse(path.begin(), path.end());}@
