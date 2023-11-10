vector<vector<ll>> dist; // Entfernung zwischen je zwei Punkten
vector<vector<int>> pre; // pre[to][from] = predecessor of to

void floydWarshall() {
	pre.assign(sz(dist), vector<int>(sz(dist), -1));
	for (int i = 0; i < sz(dist); i++) {
		for (int j = 0; j < sz(dist); j++) {
			if (dist[i][j] < INF) {
				pre[i][j] = j;
	}}}

	for (int k = 0; k < sz(dist); k++) {
		for (int i = 0; i < sz(dist); i++) {
			for (int j = 0; j < sz(dist); j++) {
				if (dist[i][j] > dist[i][k] + dist[k][j]) {
					dist[i][j] = dist[i][k] + dist[k][j];
					pre[i][j] = pre[i][k];
}}}}}
