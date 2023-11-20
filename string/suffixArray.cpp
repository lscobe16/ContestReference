struct SuffixArray {
	z n, step, count; // SA[i] = start index of i-smallest suffix
	vz SA, LCP; // LCP[i] = lcp(SA[i - 1], SA[i])
	vvz P;
	vector<pair<pair<z, z>, z>> L;

	SuffixArray(string& s) : n(s.size()), SA(n), LCP(n), L(n) {
		P = vvz(__lg(n)+2, vz(n));
		for (z i = 0; i < n; i++) P[0][i] = s[i];
		for (step = 1, count = 1; count < n; step++, count *= 2) {
			for (z i = 0; i < n; i++)
				L[i] = {{P[step-1][i],
				         i+count < n ? P[step-1][i+count] : -1}, i};
			sort(L.begin(), L.end());
			for (z i = 0; i < n; i++) {
				P[step][L[i].second] =
					i > 0 && L[i].first == L[i-1].first ?
					P[step][L[i-1].second] : i;
		}}
		for (z i = 0; i < n; i++) SA[i] = L[i].second;
		for (z i = 1; i < n; i++) LCP[i] = lcp(SA[i - 1], SA[i]);
	}

	z lcp(z x, z y) { // x and y are text-indices, not SA
		z ret = 0;
		if (x == y) return n - x;
		for (z k = step - 1; k >= 0 && x < n && y < n; k--) {
			if (P[k][x] == P[k][y]) {
				x += 1 << k;
				y += 1 << k;
				ret += 1 << k;
		}}
		return ret;
	}
};
