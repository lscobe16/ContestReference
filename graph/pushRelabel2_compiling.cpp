#include <bits/stdc++.h>
using namespace std;

#define int long long

using z = int;
using vz = vector<z>;
using vvz = vector<vz>;
using pzz = pair<z, z>;
using vpzz = vector<pzz>;
using vvpzz = vector<vpzz>;
using vb = vector<bool>;
z INF = 1e18;

#define au auto&&
#define fe(x...) for(au x)

#define in(x...) x; [](au... a){((cin>>a), ...);}(x);
#define inv(v, n) v(n); fe(_:v){in(_)}
#define dbg(x) cerr<<__LINE__<<": 	"#x" = "<<(x)<<"\n";

au operator-(ostream& o, au t) {return o << t << ' ';}
au operator+(ostream& o, au t) {return o << t << '\n';}

#define time(f...) [&](){\
	auto startT = chrono::high_resolution_clock::now(); \
	f; \
	auto stopT = chrono::high_resolution_clock::now(); \
	return chrono::duration_cast<chrono::milliseconds>(stopT - startT).count();}()


struct Edge {
	z from, to, f, c;
};

vector<Edge> edges;
// adj[v] = ids of out-edges of v
// hs[h] = list of active nodes with height h (manual bucket PQ)
vvz adj, hs; // resize adj!
// ec[v] = current excess at v
// cur[v] = lowest eligible out-edge of v
// H[v] = height of v
vz ec, cur, H; 

void addEdge(z from, z to, z c) {
	adj[from].push_back(edges.size());
	edges.push_back({from, to, 0LL, c});
	adj[to].push_back(edges.size());
	edges.push_back({to, from, 0, 0});
}

void push(z id, z f) {
	if (ec[edges[id].to] == 0 && f > 0)
		hs[H[edges[id].to]].push_back(edges[id].to); // activate
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
	vz co(2*n); // co[h] = number of nodes on height h (also inactive)
	co[0] = n - 1;
	for (z id : adj[s]) push(id, edges[id].c);
	for (z hi = 0;;) { // hi = highest active height
		while (hs[hi].empty()) if (!hi--) return -ec[s];
		z v = hs[hi].back(); hs[hi].pop_back();
		while (ec[v] > 0) {
			if (cur[v] == adj[v].size()) { // relabel
				H[v] = 2*n;
				for (z i = 0; i < adj[v].size(); i++) {
					auto [_, to, f, c] = edges[adj[v][i]];
					// find lowest (not first) eligible edge
					if (c - f > 0 && H[v] > H[to] + 1) {
						H[v] = H[to] + 1;
						cur[v] = i;
				}}
				co[H[v]]++;
				if (!--co[hi] && hi < n) {
					// height hi empty -> all nodes higher than hi cannot push back to sink
					// they are not active -> mustn't update hi
					for (z u = 0; u < n; u++) {
						if (hi < H[u] && H[u] < n) {
							co[H[u]]--;
							H[u] = n + 1;
				}}}
				hi = H[v];
			} else { // push
				auto [_, to, f, c] = edges[adj[v][cur[v]]];
				if (c - f > 0 && H[v] == H[to] + 1) {
					push(adj[v][cur[v]], min(ec[v], c - f));
				} else {
					cur[v]++;
}}}}}

// tested on: https://open.kattis.com/problems/maxflow
int32_t main() {
	z in(n, m, s, t);
	adj.resize(n);

	for (z i = 0; i < m; i++) {
		z in(a, b, c);
		addEdge(a, b, c);
	}

	z f = maxFlow(s, t);

	vz E;
	for (z i = 0; i < edges.size(); i+=2) {
		if (edges[i].f) E.push_back(i);
	}

	cout-n-f+E.size();
	fe(id:E) {
		au e = edges[id];
		cout-e.from-e.to+e.f;
	}
}
