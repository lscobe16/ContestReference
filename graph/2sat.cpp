struct sat2 {
	// insert SCC (@\page{scc}@) here
	z n;
	vz sol;

	sat2(z vars) : n(vars*2) {adj = vvz(n);};

	z pos(z i) {return 2*i;}
	z neg(z i) {return 2*i+1;} // dimacs: 2 = pos(1) ; -2 = neg(1)
	@\opt{z dimacs(z x) {return x > 0 ? pos(x-1) : neg(-x-1);}}@

	void addImpl(z a, z b) {
		adj[a].push_back(b);
		adj[1^b].push_back(1^a);
	}
	void addOr(z a, z b)    {addImpl(1^a, b);}
	@\opt{void addEquiv(z a, z b) {addImpl(a, b); addImpl(b, a);}}@
	@\opt{void addXor(z a, z b)   {addOr(a, b); addOr(1^a, 1^b);}}@
	@\opt{void addTrue(z a)       {addImpl(1^a, a);}}@
	@\opt{void addFalse(z a)      {addTrue(1^a);}}@
	@\opt{void addAnd(z a, z b)   {addTrue(a); addTrue(b);}}@
	@\opt{void addNand(z a, z b)  {addOr(1^a, 1^b);}}@

	bool solvable() {
		scc();
		for (z i = 0; i < n; i += 2) {
			if (idx[i] == idx[i + 1]) return false;
		}
		sol = vz(n, -1);
		for (z i = 0; i < sccCounter; i++) {
			if (sol[sccs[i][0]] == -1) {
				for (z v : sccs[i]) {
					sol[v] = 1;
					sol[1^v] = 0;
		}}}
		return true;
	}
};
