double shortestDist(vector<pt>& pts) { // sz(pts) > 1
	set<pt, bool(*)(pt, pt)> status(compY);
	sort(pts.begin(), pts.end(), compX);
	double opt = 1.0/0.0, sqrtOpt = 1.0/0.0;
	auto left = pts.begin(), right = pts.begin();
	status.insert(*right); right++;

	while (right != pts.end()) {
		if (left != right &&
		    abs(real(*left - *right)) >= sqrtOpt) {
			status.erase(*left);
			left++;
		} else {
			auto lower = status.lower_bound({-1.0/0.0, //-INF
			                                 imag(*right) - sqrtOpt});
			auto upper = status.upper_bound({-1.0/0.0, //-INF
			                                 imag(*right) + sqrtOpt});
			for (;lower != upper; lower++) {
				double cand = norm(*right - *lower);
				if (cand < opt) {
					opt = cand;
					sqrtOpt = sqrt(opt);
			}}
			status.insert(*right);
			right++;
	}}
	return sqrtOpt;
}
