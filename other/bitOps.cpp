// Iteriert über alle Teilmengen einer Bitmaske (außer 0)
for (z x = mask; x; --x &= mask)

// Nächste Permutation in Bitmaske (#Bits bleibt gleich)
// (z.B. 00111 => 01011 => 01101 => ...)
z nextPerm(z v) {
	z t = v | (v - 1);
	return (t+1) | (((~t & -~t) - 1) >> (__builtin_ctzll(v) + 1));
}
