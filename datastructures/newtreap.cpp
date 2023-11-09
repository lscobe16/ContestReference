z sz(auto t) {return t ? t->s : 0;}

@\yellow{using K = z;}@
using A = z;
A aggr(A a, A b) {return a+b;}
@\green{using U = z;}@
@\green{U id = 0;}@
@\green{A app(A a, U u, z s) {return a+u*s;}}@
@\green{U comp(U later, U first) {return later+first;}}@

struct treap {
    @\yellow{K k;}@
    A a;
    A agg = a;
    @\green{U lazy = id;}@ // only for children
    @\blue{z lazy_rev = 0;}@ // only use on "implicit"/non-key treaps with commutative aggr

    z prio = rand();
    treap *l = 0, *r = 0;
    z s = 1;

    @\greenE{void push() \{}\\@
        @\green{for(auto c : {l, r})}\\@
            @\green{if(c) c->apply(lazy), c->lazy_rev ^= lazy_rev;}\\@
        @\green{lazy = id;}\\@
        @\blue{if(lazy_rev) swap(l, r), lazy_rev = 0;}\\@
    @\greenE\}@

    void update() { // call after changing a or (the pointers) l or r
        s = sz(l) + sz(r) + 1;
        agg = a;
        if(l) agg = aggr(l->agg, agg);
        if(r) agg = aggr(agg, r->agg);
    }
    void seta(A _a) { a = _a; update(); }

    void apply(U u) { // apply update on range
        a = app(a, u, 1);
        agg = app(agg, u, s);
        @\green{lazy = comp(u, lazy);}@
    }
    @\blue{void rev() { lazy_rev ^= 1; }}@
};

using T = treap*;

T pair<T, T> split(T t, B b, bool after = false) { //default after = false for on, onr
    if(!t) return {t, t};
    @\green{t->push();}@
    if(b + after <= sz(t->l) || (b -= sz(t->l) + 1, 0)) {
    @\yellowBox{you MAY instead split at keys:}\\@
    @\yellow{if(after ? b < t->k : !(t->k < b)) }\yellowE\{@
        auto [l, r] = split(t->l, b, after);
        t->l = r;
        if(l) t->update();
        return {l, t};
    }
    else {
        auto [l, r] = split(t->r, b, after);
        t->r = l;
        if(r) t->update();
        return {t, r};
    }
}

T merge(T l, T r) {
    if (!l) return r;
    if (!r) return l;
    if (l->prio < r->prio) {
        @\green{l->push();}@
        l->r = merge(l->r, r);
        l->update();
        return l;
    }
    else {
        @\green{r->push();}@
        r->l = merge(l, r->l);
        r->update();
        return r;
    }
}

A e = 0; @\redBox{Check that t!=0 before accessing t->agg!}@
A auto agg(T t) {return t ? t->agg : e;}

T extract(T& t, au a, au b, bool bin = 0) {
    // for other T manipulations, copy this, ...
    au [tl, _] = split(t, a);
    au [tm, tr] = split(_, b, bin);
    // ...manipulate tm here...
    t = merge(merge(tl, 0), tr); // ...and replace 0 with tm
    return tm;
}

void insert(T& t, T o, au b, bool after = 0) {
    au [tl, _] = split(t, b, after);
    au [tm, tr] = split(_, b, after);
    tm = o;
    t = merge(merge(tl, tm), tr);
}
