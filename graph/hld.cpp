vector<vector<int>> adj;
vector<int> sz, in, head, par;
int counter;

void dfs_sz(int v = 0, int from = -1) {
	for (auto& u : adj[v]) if (u != from) {
		dfs_sz(u, v);
		sz[v] += sz[u];
		if (adj[v][0] == from || sz[u] > sz[adj[v][0]]) {
			swap(u, adj[v][0]); //changes adj!
}}}

void dfs_hld(int v = 0, int from = -1) {
	par[v] = from;
	in[v] = counter++;
	for (int u : adj[v]) if (u != from) {
		head[u] = (u == adj[v][0]) ? head[v] : u;
		dfs_hld(u, v);
	}
}

void init(int root = 0) {
	int n = sz(adj);
	sz.assign(n, 1), head.assign(n, root), par.assign(n, -1);
	in.resize(n);
	counter = 0;
	dfs_sz(root);
	dfs_hld(root);
}

template<typename F>
void for_intervals(int u, int v, F&& f) {
	for (;; v = par[head[v]]) {
		if (in[v] < in[u]) swap(u, v);
		f(max(in[u], in[head[v]]), in[v] + 1);
		if (in[head[v]] <= in[u]) return;
}}

int get_lca(int u, int v) {
	for (;; v = par[head[v]]) {
		if (in[v] < in[u]) swap(u, v);
		if (in[head[v]] <= in[u]) return u;
}}
