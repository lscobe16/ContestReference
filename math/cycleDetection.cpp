pzz cycleDetection(z x0, au f) { // f: z -> z
	z a = x0, b = f(x0), len = 1;
	for (z power = 1; a != b; b = f(b), len++) {
		if (power == len) {
			power *= 2, len = 0, a = b;
	}}
	z start = 0; a = x0; b = x0;
	for (z i = 0; i < len; i++) b = f(b);
	while (a != b) a = f(a), b = f(b), start++;
	return {start, len};
}
