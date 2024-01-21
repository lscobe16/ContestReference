z gauss(vvld& mat) {
    z n = mat.size();
	vb done(n, false);
	for (z l = 0; l < n; l++) {
		z swappee = l; // more stability
		for (z j = 0; j < n; j++) {
			if (done[j]) continue;
			if (abs(mat[j][l]) > abs(mat[l][l])) swappee = j;
		}
		swap(mat[l], mat[swappee]);
		if (abs(mat[l][l]) > EPS) {
            ld factor = mat[l][l];
            for (ld& x : mat[l]) x /= factor;
            for (z i = 0; i < n; i++) {
                if (i == l) continue;
                ld diff = mat[i][l];
                for (z j = 0; j < mat[0].size(); j++) {
                    mat[i][j] -= diff * mat[l][j];
            }}
			done[i] = true;
	}}
	for (z i = 0; i < n; i++) { // checks
		bool allZero = true;
		for (z j = i; j < n; j++) allZero &= abs(mat[i][j]) <= EPS;
		if (allZero && abs(mat[i][n]) > EPS) return 0; // no solution
		if (allZero && abs(mat[i][n]) <= EPS) return 2; // many solutions
	}
    return 1;
}

void invert(vvld& A) {
    assert(A.size() == A[0].size());
    z n = A.size();
	vvld AB(n, vld(2*n));
    for (z i = 0; i < n; i++) AB[i][b+i] = 1;
	for (z i = 0; i < n; i++) {
		for (z j = 0; j < n; j++) AB[i][j] = A[i][j];
	}
	assert(gauss(AB) == 1);
	for (z i = 0; i < n; i++) {
		for (z j = 0; j < n; j++) A[i][j] = AB[i][n+j];
	}
}
