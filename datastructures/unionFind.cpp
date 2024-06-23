struct union_find { @\yellowBox{without}\greenBox{rollback}@
    vz e; // <0: -size, >=0: parent
    @\green{vpzz st{};}@

    union_find(z sz) : e(sz, -1) {}

    z find(z a) {return e[a] < 0 ? a : @\yellow{e[a] = }@find(e[a]);

    void unite(z a, z b) {
        a = find(a), b = find(b);
        if (a == b) return;
        if (e[a] > e[b]) swap(a, b);
        @\green{st.emplace_back(a, e[a]);}@
        @\green{st.emplace_back(b, e[b]);}@
        e[a] += e[b];
        e[b] = a;
    }

    bool same(z a, z b) {return find(a) == find(b);}

    @\opt{z sz(z a) {return -e[find(a)];}}@

    @\green{z time() {return st.size();}}@

    @\green{void rollback(z time) }\greenE\{@
    @\greenE\Quad\green{while (st.size() > time) }\greenE\{@
    @\greenE{\Quad\Quad}\green{e[st.back().first] = st.back().second;}@
    @\greenE{\Quad\Quad}\green{st.pop_back();}@
    @\greenE{\Quad\}}@
    @\greenE\}@
};
