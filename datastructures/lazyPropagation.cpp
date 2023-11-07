struct segT {
    z sz; @\warn{always initialize!}@

    using A=z;
    using U=z;
    A e = 0;
    U id = 0;
    A aggr(A a, A b) {return a+b;}
    A app(A a, U u, z s) {return a+u*s;}
    U comp(U later, U first) {return later+first;}

    struct node {
        int32_t l, r;
        A agg; //or value (for leaves)
        U lazy;
    };    @\orangeBox{persistent}\yellowBox{not persistent}@
    @\yellow{vector<node> v={{0, 0, e, id}};}@
    @\orange{shared_ptr<vector<node>> v{new vector<node>({0, 0, e, id})};}@ 
    //Array wegen Speicher (int32_t < node*). Is that worth it??? // Linus: probably this is also faster because of caching
    //shared_ptr: bei vielen Updates/SegTs ist es wichtig, dass der Speicher für v wieder freigegeben wird
@\orange{#define v (*v)}@
#define N v[n]
    z root = 0;

    z set(z n, node x) {
        return @\yellow{n ? v[n]=x, n : }@(v.push_back(x), v.size()-1);
    }
    z apply(z n, U u, z rangesize) {
        return set(n, {N.l, N.r, app(N.agg, u, rangesize), comp(u, N.lazy)});
    }
    z update(z a, z bex, z l, z rex, z n, U u) { //TODO: make update and apply return nodes (that need to be pushed into v manually, if desired)!!?
        if(bex <= l || rex <= a) return n;
        if(a <= l && rex <= bex) return apply(n, u, rex - l);
        z m = (l + rex) / 2;
        z nl = update(a, bex, l, m, apply(N.l, N.lazy, m - l), u); //here, it's important that v[0] is an empty node
        z nr = update(a, bex, m, rex, apply(N.r, N.lazy, rex - m), u);
        return set(n, {nl, nr, aggr(v[nl].agg, v[nr].agg)});
    }
    A query(z a, z bex, z l, z rex, z n) {
        if(bex <= l || rex <= a) return e;
        if(a <= l && rex <= bex) return N.agg;
        //push(n, rex - l); //might need to much memory if more queries than updates allowed
        z m = (l + rex) / 2;
        A la = query(a, bex, l, m, N.l), ra = query(a, bex, m, rex, N.r);
        return app(aggr(la, ra), N.lazy, min(bex, rex) - max(a, l));
    }

    z bin_search(z a, z bex, z l, z rex, z n, A &cur_agg, U lazy, function<bool(A&)> &p@\opt{, bool rtl}@) { @\optAnn@
        if(bex <= l || rex <= a) return -1; //todo: bei Link anders -- passt das so (immer)? Chris fragen!?
        A n_agg = app(N.agg, lazy, rex - l);
        A new_agg = @\opt{rtl ? aggr(n_agg, cur_agg) : }@aggr(cur_agg, n_agg);
        if (a <= l && rex <= bex && !p(new_agg)) return cur_agg = new_agg, -1;
        if (l + 1 == rex) return l;

        //push(n, rex - l); //might need to much memory if more queries than updates allowed
        z m = (l + rex) / 2;
        z res = bin_search(a, bex, @\opt{rtl?m:}@l, @\opt{rtl?rex:}@m, @\opt{rtl?N.r:}@N.l, cur_agg, lazy = comp(lazy, N.lazy), p, rtl);
        if (res != -1) return res;
        return bin_search(a, bex, @\opt{rtl?l:}@m, @\opt{rtl?m:}@rex, @\opt{rtl?N.l:}@N.r, cur_agg, lazy, p, rtl);
    }
#undef N
@\orange{#undef v}@

    @\yellow{void}\orange{segT}@ update(z l, z rex, U u) {
        @\opt{assert(0 <= l && l <= rex && rex <= sz);}@
        @\yellow{this->root = update(l, rex, 0, sz, root, u);}@
        @\orange{return segT{sz, e, id, v, update(l, rex, 0, sz, root, u)};}@
    }

    A query(z l, z rex) {
        @\opt{assert(0 <= l && l <= rex && rex <= sz);}@
        return query(l, rex, 0, sz, root);
    }

    //todo: unschön (siehe auch treap): wenn schon p(neutralE), wird l zurückgegeben
    //left_to_right:
    //  returns smallest k in [l, rex) so that p(agg(a_l, ..., a_k)), or -1 if impossible
    //  p should be increasing, i.e.  p(a1) not less than p(agg(a1, a2))
    //right_to_left:
    //  returns largest k in [l, rex) so that p(agg(a_k, ..., a_rex-1)), or -1 if impossible
    //  p should be decreasing, i.e.  p(a1) not greater than p(agg(a1, a2))
    z bin_search(z l, z rex, function<bool(A&)> p@\opt{, bool right_to_left = false}@) { @\optAnn@
        @\opt{assert(0 <= l && l <= rex && rex <= sz);}@
        if(l==rex) return -1;
        A curr_agg = e;
        return bin_search(l, rex, 0, sz, root, curr_agg, id, p@\opt{, right_to_left}@);
    }
};