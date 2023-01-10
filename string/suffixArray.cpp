struct SuffixArray {
	vector<pair<pair<int, int>, int>> L;
	int n, step, count;
	vector<vector<int>> P;
	vector<int> SA, LCP; 

	SuffixArray(const string& s) : n(sz(s)) {
		SA.resize(n); LCP.resize(n); L.resize(n);
		P.assign(__ln(n)*4-2, vector<int>(n));
		for (int i = 0; i < n; i++) P[0][i] = s[i];
		for (step = 1, count = 1; count < n; step++, count *= 2) {
			for (int i = 0; i < n; i++)
				L[i] = {{P[step-1][i], 
				         i+count < n ? P[step-1][i+count] : -1}, i};
			sort(all(L));
			for (int i = 0; i < n; i++) {
				P[step][L[i].second] = 
					i > 0 && L[i].first == L[i-1].first ?
					P[step][L[i-1].second] : i;
		}}
		for (int i = 0; i < n; i++) SA[i] = L[i].second;
		for (int i = 1; i < n; i++) LCP[i] = lcp(SA[i - 1], SA[i]);
	}

	// x and y are text-indices, not SA-indices.
	int lcp(int x, int y) {
		int ret = 0;
		if (x == y) return n - x;
		for (int k = step - 1; k >= 0 && x < n && y < n; k--)
			if (P[k][x] == P[k][y]) {
				x += 1 << k;
				y += 1 << k;
				ret += 1 << k;
			}
		return ret;
	}
};
