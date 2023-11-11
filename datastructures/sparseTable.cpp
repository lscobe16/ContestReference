struct SparseTable {
	z n; vz a; vvz st;

	// @\orangeBox{config}@  default: min
	z better(z l, z r) { // idempotent, indices!
		return a[l] @\orange{<=}@ a[r] ? l : r; 
	}
	
	SparseTable(vz &vec): 
		n(vec.size()), a(vec), st(__lg(n)+1, vz(n)) {
		iota(be(st[0]), 0);
		for (z j = 0; (2 << j) <= n; j++) {
			for (z i = 0; i + (2 << j) <= n; i++) {
				st[j + 1][i] = better(st[j][i], st[j][i + (1 << j)]);
	}}}

	z queryIndex(z l, z rex) {
		@\opt{assert(0 <= l && l <= rex && rex <= n);}@ // rex>n => UB
		@\optE{if (l == rex) return \orange{INF};}@ // neutrales Element
		z j = __lg(rex - l);
		return better(st[j][l], st[j][rex - (1 << j)]);
	}
};
