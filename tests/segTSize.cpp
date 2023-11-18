int32_t main() {
	z n = 1e5;
	sz = n;
	vector<segT> v={{segT()}};
	for (int i = 0; i < n; ++i) {
		segT t = v.back();
        t = t.update(n-1, n, 1);
		v.push_back(t);
	}
	cout-"average nodes per update"+v[0].v->size()/(2*n);
	// sleep(999999); // to read memory from "watch free" locally
	cout+v.back().query(0,n); // to prevent over-optimization
}
