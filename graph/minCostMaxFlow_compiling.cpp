#include <bits/stdc++.h>
using namespace std;

#define int long long

using z = int;
using vz = vector<z>;
using vb = vector<bool>;
using vvz = vector<vz>;
using pzz = pair<z, z>;
using vpzz = vector<pzz>;
using vvpzz = vector<vpzz>;
z INF = 1e18;

#define au auto&&
#define fe(x...) for(au x)

#define in(x...) x; [](au... a){((cin>>a), ...);}(x);
#define inv(v, n) v(n); fe(_:v){in(_)}



struct MinCostFlow {
	struct edge {
		z to, f, cost;
	};
	vector<edge> E;
	vvz adj;
	vz pref, con, dist;

	z n, s, t, maxFlow, minCost;

	MinCostFlow(z n, z source, z target) :
		n(n), adj(n), s(source), t(target) {};

	void addEdge(z u, z v, z c, z cost) {
		adj[u].push_back(E.size());
		E.push_back({v, c, cost});
		adj[v].push_back(E.size());
		E.push_back({u, 0, -cost});
	}

	bool spfa() {
		pref = vz(n, -1);
		dist = vz(n, INF);
		vb inQ(n);
		queue<z> Q;

		dist[s] = 0;
		Q.push(s);
		pref[s] = s;
		inQ[s] = true;

		while (!Q.empty()) {
			z cur = Q.front(); Q.pop();
			inQ[cur] = false;
			for (z id : adj[cur]) {
				z to = E[id].to;
				if (E[id].f > 0 &&
				    dist[to] > dist[cur] + E[id].cost) {
					dist[to] = dist[cur] + E[id].cost;
					pref[to] = cur;
					con[to] = id;
					if (!inQ[to]) {
						inQ[to] = true;
						Q.push(to);
		}}}}
		return pref[t] != -1;
	}

	void extend() {
		z w = INF;
		for (z u = t; pref[u] != u; u = pref[u])
			w = min(w, E[con[u]].f);
		maxFlow += w;
		minCost += dist[t] * w;
		for (z u = t; pref[u] != u; u = pref[u]) {
			E[con[u]].f -= w;
			E[con[u] ^ 1].f += w;
	}}

	void minCostFlow() { // successive shortest path
		con.assign(n, 0);
		maxFlow = minCost = 0;
		while (spfa()) extend();
}};

// tested on: https://open.kattis.com/problems/mincostmaxflow
int32_t main() {
	cin.tie(0)->sync_with_stdio(0);
	
	z in(n, m, s, t);
	MinCostFlow F(n, s, t);

	for (z i = 0; i < m; i++) {
		z in(a, b, c, w);
		F.addEdge(a, b, c, w);
	}

	F.minCostFlow();

	cout << F.maxFlow << " " << F.minCost << endl;
}
