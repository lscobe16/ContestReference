//Options: agg(+lazy update) (+rev) OR key

z sz(auto t) {return t ? t->s : 0;}

@\yellow{using K = z;}@ // key
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

    @\green{void push()}\\@
        @\green{for(auto c : {l, r})}\\@
            @\green{if(c) c->apply(lazy), c->lazy_rev ^= lazy_rev;}\\@
        @\green{lazy = id;}\\@
        @\blue{if(lazy_rev) swap(l, r), lazy_rev = 0;}\\@
    @\green{}@

    void update(){ // call after changing a or (the pointers) l or r
        s = sz(l) + sz(r) + 1;
        agg = a;
        if(l) agg = aggr(l->agg, agg);
        if(r) agg = aggr(agg, r->agg);
    }
    void seta(A _a) {
        a = _a;
        update();
    }

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
    @\yellowBox{MAY be used instead of the line above IF using keys:}\\@
    @\yellow{if(after ? b < t->k : !(t->k < b)) }@
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

@\red{A e = 0;}@
@\red{A auto agg(T t) {return t ? t->agg : e;}}@
