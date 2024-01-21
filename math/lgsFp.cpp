z gauss(vvz& mat, z mod=MOD) {
	z n = mat.size();
	for (z l = 0; l < n; l++) {
		z j = l;
		while (j < n && mat[j][l] == 0) j++;
		if (j == n) continue;
		swap(mat[l], mat[j]);
		z factor = multInv(mat[l][l], mod);
		for (z& x : mat[l]) x = (x * factor) % mod;
		for (z i = 0; i < n; i++) {
			if (i == l) continue;
			z diff = mat[i][l];
			for (z j = 0; j < mat[0].size(); j++) {
				mat[i][j] -= (diff * mat[l][j]) % mod;
				mat[i][j] = (mat[i][j] + mod) % mod;
	}}}
	@\greenE{for (z i = 0; i < n; i++) \{}@ @\greenBox{checks für inhomogene LGS}@
		@\green{bool allZero = true;}@
		@\green{for (z j = i; j < n; j++) allZero &= abs(mat[i][j]) == 0;}@
		@\green{if (allZero && mat[i][n] != 0) return 0;}@ @\greenBox{no solution}@
		@\green{if (allZero && mat[i][n] == 0) return 2;}@ @\greenBox{many solutions}@
	@\greenE{\}}@
	return 1;
}
// invertieren siehe oben
