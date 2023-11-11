struct iterSegT {
    using A = z;
    A e = 0;
    A agg(A a, A b) {return a+b;}

    z n;
    vector<A> v;

    iterSegT(z n): n(n), v(2 * n, e) {}
    iterSegT(vector<A> s): n(s.size()), v(n, e) {
        v.insert(v.end(), be(s));
        @\green{for (z i = n; i-- > 0;)}@
            @\green{v[i] = agg(v[2 * i], v[2 * i + 1]);}@
    }

    @\greenBox{Point set, Range mark}@
    void set(z i, A a) {
        v[i += n] = a;
        while (i /= 2) v[i] = agg(v[2 * i], v[2 * i + 1]);
    }

    A query(z l, z rex) {
        A la = e, ra = e;
        for (l += n, rex += n; l < rex; l /= 2, rex /= 2) {
            if (l&1) la = agg(la, v[l++]);
            if (rex&1) ra = agg(v[--rex], ra);
        }
        return agg(la, ra);
    }

    @\yellowBox{Range apply, Point query}@
    void update(z l, z rex, A a) {
        for (l += n, rex += n; l < rex; l /= 2, rex /= 2) {
            if (l&1) {v[l] = agg(v[l], a), l++;}
            if (rex&1) {--rex, v[rex] = agg(v[rex], a);}
    }}

    A query(z i) {
        A r = v[i += n];
        while(i /= 2) r = agg(r, v[i]);
        return r;
}};