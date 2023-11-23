constexpr z N = 10'000'000;
vz, div(N); // 0 <=> prime

vz sieve(z n) {@\orangeBox{greatest divisor}@  @\greenBox{fast}@
	div[0] = div[1] = 1;

	for (z i = 3; i < n; i++) {
		@\green{if (i % 2 == 0) div[i] = 2;}@
		else if (!div[i]) {
			@\greenE{for (z j = i*i; j < n; j += i*2) div[j] = i;}@
			@\orangeE{for (z j = i+i; j < n; j += i) div[j] = i;}@
		}
	}
	return div;
}
