struct segT { @\warn{bei persistent vorm Abschreiben memory berechnen!}@
    z sz; @\warn{always initialize!}@

    using A = z;
    using U = z;
    A e = INF;
    U id = -1;
    A aggr(A a, A b) {return min(a, b);}
    A app(A a, U u, z s) {return u!=id ? u : a;} // s: rangesize
    U comp(U later, U first) {return later!=id ? later : first;}

    struct node {
        int32_t l, r;
        A agg; //or value (for leaves)
        U lazy;
    };    @\greenBox{not persistent}@  @\yellowBox{persistent}@
    @\yellow{shared_ptr<}@vector<node>@\yellow>@ v@\yellowE{\{new vector<node>}@{{0, 0, e, id}}@\yellowE\}@;
@\yellowE{\#define v (*v)}@
#define N v[n]
    z root = 0;

    z set(@\green{z n, }@node x) {
        return @\green{n ? v[n]=x, n : }\red(@v.push_back(x), v.size()-1@\red)@;
    }
    z apply(z n, U u, z s) {
        return set(@\green{n, }@{N.l, N.r, app(N.agg, u, s), comp(u, N.lazy)});
    }
	z update(z a, z bex, z l, z rex, z n, U u, U lazy) {
		if(bex <= l || rex <= a) return apply(n, lazy, rex - l);
		if(a <= l && rex <= bex) return apply(n, comp(u, lazy), rex - l);
		z m = (l+rex)/2;
		z nl = update(a, bex, l, m, N.l, u, comp(lazy, N.lazy));
		z nr = update(a, bex, m, rex, N.r, u, comp(lazy, N.lazy));
		return set(@\green{n, }@{nl, nr, aggr(v[nl].agg, v[nr].agg), id});
	}
    A query(z a, z bex, z l, z rex, z n) {
        if(bex <= l || rex <= a) return e;
        if(a <= l && rex <= bex) return N.agg;
        z m = (l + rex) / 2;
        A la = query(a, bex, l, m, N.l);
        A ra = query(a, bex, m, rex, N.r);
        return app(aggr(la, ra), N.lazy, min(bex, rex) - max(a, l));
    }

    z lower_bound(z a, z bex, z l, z rex, z n, @\optAnn@
           A &cur_agg, U lazy, function<bool(A&)> &p@\opt{, bool rtl}@) {
        if(bex <= l || rex <= a) return -2;
        A n_agg = app(N.agg, lazy, rex - l);
        A new_agg = @\opt{rtl ? aggr(n_agg, cur_agg) : }@aggr(cur_agg, n_agg);
        if (a <= l && rex <= bex && !p(new_agg)) return cur_agg = new_agg, -2;
        if (l + 1 == rex) return l;
        z m = (l + rex) / 2;
        z res = lower_bound(a, bex, @\opt{rtl?m:}@l, @\opt{rtl?rex:}@m, @\opt{rtl?N.r:}@N.l, cur_agg, lazy = comp(lazy, N.lazy), p, rtl);
        if (res != -2) return res;
        return lower_bound(a, bex, @\opt{rtl?l:}@m, @\opt{rtl?m:}@rex, @\opt{rtl?N.l:}@N.r, cur_agg, lazy, p, rtl);
    }
#undef N
@\yellowE{\#undef v}@

    @\green{void}\yellow{segT}@ update(z l, z rex, U u) {
        @\opt{assert(0 <= l && l <= rex && rex <= sz);}@
        @\green{root = update(l, rex, 0, sz, root, u);}@
        @\yellow{return segT{sz, e, id, v, update(l, rex, 0, sz, root, u, id)};}@
    }

    A query(z l, z rex) {
        @\opt{assert(0 <= l && l <= rex && rex <= sz);}@
        return query(l, rex, 0, sz, root);
    }

    z lower_bound(z l, z rex, @\optAnn@
            function<bool(A&)> p @\opt{, bool rtl = false}@) {
        @\opt{assert(0 <= l && l <= rex && rex <= sz);}@
        if(p(e)) return @\opt{rtl?rex:}@l;
        if(l==rex) return -1;
        A curr_agg = e;
        return lower_bound(l, rex, 0, sz, root, curr_agg, id, p@\opt{, rtl}@) + @\opt{rtl?0:}@1;
}};