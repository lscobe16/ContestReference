#include "../template/template_compiling.cpp"

template<bool persistent=0>
struct segT {
    z sz; //always initialize!

 	/*//main0:
	using A = z;
	using U = z;
	A e = INF;
	U id = -1;
	A aggr(A a, A b) {return min(a, b);}
    A app(A a, U u, z s) {return u!=id ? u : a;}
    U comp(U later, U first) {return later!=id ? later : first;}*/

	/*//main1:
	using A = z;
	using U = z;
	A e = 0;
	U id = 0;
	A aggr(A a, A b) {return a+b;}
	A app(A a, U u, z s) {return a+u*s;}
	U comp(U later, U first) {return later+first;}*/

	/*//main2:
	using A = z;
	using U = pzz;
	z M = 998244353;
	A e = 0;
	U id = {1,0};
	A aggr(A a, A b) {return (a+b)%M;}
	A app(A a, U u, z s) {return (u.first*a + u.second*s)%M;}
	U comp(U later, U first) {return {(later.first*first.first)%M, (later.first*first.second + later.second)%M};}*/

    struct node {
        int32_t l, r;
        A agg; //or value (for leaves)
        U lazy;
    };
    shared_ptr<vector<node>> v{new vector<node>{{0, 0, e, id}}}; //Array wegen Speicher (int32_t < node*). Is that worth it??? // Linus: probably this is also faster because of caching
                                                                 //shared_ptr: bei vielen Updates/SegTs ist es wichtig, dass der Speicher für v wieder freigegeben wird
#define v (*v)
#define N v[n]
    z root = 0;

    z set(z n, node x) {
        return persistent || !n ? v.push_back(x), v.size()-1 : (v[n]=x, n);
    }
    z apply(z n, U u, z s) {
        return set(n, {N.l, N.r, app(N.agg, u, s), comp(u, N.lazy)});
    }
	/*old version (if persistent: 1/3 more memory. TODO: Delete when tested NE!!!: mit dem TODO unten könnte das hier einfacher sein)
    z update(z a, z bex, z l, z rex, z n, U u) {
        if(bex <= l || rex <= a) return n;
        if(a <= l && rex <= bex) return apply(n, u, rex - l);
        z m = (l + rex) / 2;
        z nl = update(a, bex, l, m, apply(N.l, N.lazy, m - l), u); //here, it's important that v[0] is an empty node
        z nr = update(a, bex, m, rex, apply(N.r, N.lazy, rex - m), u);
        return set(n, {nl, nr, aggr(v[nl].agg, v[nr].agg), id});
    }*/
	z update(z a, z bex, z l, z rex, z n, U u, U lazy) { //TODO: make update and apply return nodes (that need to be pushed into v manually, if desired)!!?
		if (bex <= l || rex <= a) return apply(n,lazy,rex-l);
		if (a <= l && rex <= bex) return apply(n, comp(u, lazy), rex-l);
		z m = (l+rex)/2;
		z nl = update(a, bex, l, m, N.l, u, comp(lazy, N.lazy)); //here, it's important that v[0] is an empty node
		z nr = update(a, bex, m, rex, N.r, u, comp(lazy, N.lazy));
		return set(n, {nl, nr, aggr(v[nl].agg, v[nr].agg), id});
	}
    A query(z a, z bex, z l, z rex, z n) {
        if(bex <= l || rex <= a) return e;
        if(a <= l && rex <= bex) return N.agg;
        //push(n, rex - l); //might need to much memory if more queries than updates allowed
        z m = (l + rex) / 2;
        A la = query(a, bex, l, m, N.l);
        A ra = query(a, bex, m, rex, N.r);
        return app(aggr(la, ra), N.lazy, min(bex, rex) - max(a, l));
    }

    z lower_bound(z a, z bex, z l, z rex, z n, A &cur_agg, U lazy, function<bool(A&)> &p, bool rtl) {
        if(bex <= l || rex <= a) return -2; //todo: bei Link anders -- passt das so (immer)? Chris fragen!?
        A n_agg = app(N.agg, lazy, rex - l);
        A new_agg = rtl ? aggr(n_agg, cur_agg) : aggr(cur_agg, n_agg);
        if (a <= l && rex <= bex && !p(new_agg)) return cur_agg = new_agg, -2;
        if (l + 1 == rex) return l;

        //push(n, rex - l); //might need to much memory if more queries than updates allowed
        z m = (l + rex) / 2;
        z res = lower_bound(a, bex, rtl?m:l, rtl?rex:m, rtl?N.r:N.l, cur_agg, lazy = comp(lazy, N.lazy), p, rtl);
        if (res != -2) return res;
        return lower_bound(a, bex, rtl?l:m, rtl?m:rex, rtl?N.l:N.r, cur_agg, lazy, p, rtl);
    }
#undef N
#undef v

    segT update(z l, z rex, U u) {
        assert(0 <= l && l <= rex && rex <= sz);
        segT t = *this;
        t.root = update(l, rex, 0, sz, root, u, id);
        if(!persistent) root = t.root;
        return t;
    }

    A query(z l, z rex) {
        assert(0 <= l && l <= rex && rex <= sz);
        return query(l, rex, 0, sz, root);
    }

    z lower_bound(z l, z rex, function<bool(A&)> p , bool rtl = false) {
        assert(0 <= l && l <= rex && rex <= sz);
        if(p(e)) return rtl?rex:l;
        if(l==rex) return -1;
        A curr_agg = e;
        return lower_bound(l, rex, 0, sz, root, curr_agg, id, p, rtl) + !rtl;
}};

/*
int32_t main0() { // https://judge.yosupo.jp/problem/segment_add_get_min
	z in(n,q)
	segT<0> t{n};
	for (int i = 0; i < n; ++i) {
		z in(a)
		t.update(i,i+1,a);
	}
	for (int i = 0; i < q; ++i) {
		z in(l,rex)
		pr+t.query(l,rex);
	}
}*/

/*int32_t main1() { // https://judge.yosupo.jp/problem/point_add_range_sum
	z in(n,q)
	segT<0> t{n};
	for (int i = 0; i < n; ++i) {
		z in(a)
		t.update(i,i+1,a);
	}
	for (int i = 0; i < q; ++i) {
		z in(m)
		if(m==0) {
			z in(p,x)
			t.update(p,p+1,x);
		}
		else {
			z in(l,rex)
			pr+t.query(l,rex);
		}
	}
}*/

/*int32_t main2() { // https://judge.yosupo.jp/problem/range_affine_range_sum
	z in(n,q)
	segT<0> t{n};
	for (int i = 0; i < n; ++i) {
		z in(a)
		t.update(i,i+1, {0, a});
	}
	for (int i = 0; i < q; ++i) {
		z in(m)
		if(m==0) {
			z in(l,rex,b,c)
			t.update(l,rex,{b,c});
		}
		else {
			z in(i)
			pr+t.query(i,i+1);
		}
	}
}*/

//TODO: test persistency (e.g. with SWERC task  --  when CF is available again)

//TODO: test lower_bound
