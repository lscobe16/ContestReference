void gauss(vvz& mat, z mod) {
	z n = mat.size()
	vb done(n, false);
	for (z l = 0; l < n; l++) {
		z j = 0;
		while (j < n && (done[j] || mat[j][l] == 0)) j++;
		if (j == n) continue;
		swap(mat[l], mat[j]);
		z factor = multInv(mat[l][l], p);
		for (z& x : mat[l]) x = (x * factor) % p;
		for (z i = 0; i < n; i++) {
			if (i == l) continue;
			z diff = mat[i][l];
			for (z j = 0; j <= n; j++) {
				mat[i][j] -= (diff * mat[l][j] + p) % p;
		}}
		done[i] = true;
}} // 0/1/viele Lösungen siehe oben
