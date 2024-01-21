z gauss(vvld& mat) {
	z n = mat.size();
	for (z l = 0; l < n; l++) {
		z swappee = l; // more stability
		for (z j = l+1; j < n; j++)
			if (abs(mat[j][l]) > abs(mat[swappee][l])) swappee = j;
		cerr+swappee;
		swap(mat[l], mat[swappee]);
		if (abs(mat[l][l]) > EPS) {
			ld factor = mat[l][l];
			for (ld& x : mat[l]) x /= factor;
			for (z i = 0; i < n; i++) {
				if (i == l) continue;
				ld diff = mat[i][l];
				for (z j = 0; j < mat[0].size(); j++) {
					mat[i][j] -= diff * mat[l][j];
	}}}}
	@\greenE{for (z i = 0; i < n; i++) \{}@ @\greenBox{checks für inhomogene LGS}@
		@\green{bool allZero = true;}@
		@\green{for (z j = i; j < n; j++) allZero &= abs(mat[i][j]) <= EPS;}@
		@\green{if (allZero && abs(mat[i][n]) > EPS) return 0;}@ @\greenBox{no solution}@
		@\green{if (allZero && abs(mat[i][n]) <= EPS) return 2;}@ @\greenBox{many solutions}@
	@\greenE{\}}@
	return 1;
}

void invert(vvld& A) {
	@\opt{assert(A.size() == A[0].size());}@
	z n = A.size();
	vvld AB(n, vld(2*n));
	for (z i = 0; i < n; i++) AB[i][n+i] = 1;
	for (z i = 0; i < n; i++)
		for (z j = 0; j < n; j++) AB[i][j] = A[i][j];
	@\opt{assert(}@gauss(AB)@\opt{ == 1)}@; @\greenBox{checks == 1 iff A regular}@
	for (z i = 0; i < n; i++)
		for (z j = 0; j < n; j++) A[i][j] = AB[i][n+j];
}
