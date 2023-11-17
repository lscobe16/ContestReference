using uz = unsigned long long; // not: unsigned z!
uz modmul(uz a, uz b, uz M) {
	z ret = a * b - M * uz(1.L / M * a * b);
	return ret + M * (ret < 0) - M * (ret >= (z)M);
}
uz modpow(uz b, uz e, uz M) {
	uz ans = 1;
	for (; e; b = modmul(b, b, M), e /= 2)
		if (e & 1) ans = modmul(ans, b, M);
	return ans;
}
