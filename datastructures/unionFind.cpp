struct union_find {
    vz e; // <0: -rank(~height)/@\yellow{size}@, >=0: parent
    @\green{vpzz st{};}@ @\greenBox{rollback}@

    union_find(z sz) : e(sz, -1) {}

    z find(z a) {return e[a] < 0 ? a : e[a] = find(e[a]);}

    void unite(z a, z b) {
        a = find(a), b = find(b);
        if (a == b) return;
        if (e[a] > e[b]) swap(a, b);
        @\green{st.emplace_back(a, e[a]);}@
        @\green{st.emplace_back(b, e[b]);}@
        e[a] -= e[a] == e[b]; @\yellowBox{by size: instead e[a]+=e[b] (slower)}@
        e[b] = a;
    }

    bool same(z a, z b) {return find(a) == find(b);}

    @\yellow{z sz(z a) {return -e[find(a)];}}@

    @\green{z time() {return st.size();}}@

    @\green{void rollback(z time) }\greenE\{@
    @\greenE\Quad\green{fe([a, x]:vpzz(time + st.begin(), st.end())) e[a] = x;}@
    @\greenE\Quad\green{st.resize(time);}@
    @\greenE\}@
};
