vector<pt> convexHull(vector<pt> pts){
	sort(all(pts), [](au a, au b){
        return pair{a.real(), a.imag()} < pair{b.real(), b.imag()};
	});
	pts.erase(unique(all(pts)), pts.end());
	int k = 0;
	vector<pt> h(2 * sz(pts));
	for (int i = 0; i < sz(pts); i++) {// Untere Hülle.
		while (k > 1 && cross(h[k-2], h[k-1], pts[i]) <= 0) k--;
		h[k++] = pts[i];
	}
	for (int i = sz(pts)-2, t = k; i >= 0; i--) {// Obere Hülle.
		while (k > t && cross(h[k-2], h[k-1], pts[i]) <= 0) k--;
		h[k++] = pts[i];
	}
	h.resize(k);
	return h;
}
