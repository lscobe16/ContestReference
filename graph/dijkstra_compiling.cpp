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



// adj[i] = {(j, c(e)) | (i, j) = e in E}
using pzz = pair<z, z>; //dist, destination
pair<vz, vz> dijkstra(vvpzz& adj, z start) {
	priority_queue<pzz, vpzz, greater<pzz>> Q;
	vz dist(adj.size(), INF), prev(adj.size(), -1);
	dist[start] = 0; Q.emplace(0, start);

	while (Q.size()) {
		auto [du, u] = Q.top(); Q.pop();
		if (du > dist[u]) continue; // lazy decreaseKey
		fe([v, c] : adj[u]) {
			if (du + c < dist[v]) {
				dist[v] = du + c;
				prev[v] = u;
				Q.emplace(dist[v], v);
	}}}
	return {dist, prev};
}

int32_t main() {
	z in(n, m, s, t);
	vvpzz G(n);
	for (z i = 0; i < m; i++) {
		z in(a, b, c);
		G[a].push_back({b, c});
	}

	auto [dist, prev] = dijkstra(G, s);

	if (dist[t] == INF) {
		cout+(-1);
		return 0;
	}

	vz path = {{t}}; z c = t;
	while (c != s) path.push_back(c = prev[c]);
	reverse(path.begin(), path.end());

	cout-dist[t]+(path.size()-1);
	for (z i = 0; i < path.size()-1; i++) {
		cout-path[i]+path[i+1];
	}
}
