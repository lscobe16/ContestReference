constexpr z bases32[] = {2, 7, 61};
constexpr z bases64[] = {2, 325, 9375, 28178, 450775,
                          9780504, 1795265022};
bool isPrime(z n) {
	if (n < 2 || n % 2 == 0) return n == 2;
	z d = n - 1, j = 0;
	while (d % 2 == 0) d /= 2, j++;
	for (z a : bases64) {
		if (a % n == 0) continue;
		z v = modpow(a, d, n);
		if (v == 1 || v == n - 1) continue;
		for (z i = 1; i <= j; i++) {
			v = ((__int128)v * v) % n;
			if (v == n - 1 || v <= 1) break;
		}
		if (v != n - 1) return false;
	}
	return true;
}
