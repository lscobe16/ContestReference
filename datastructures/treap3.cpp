@\yellow{using K = z;}@
using A = z;
A aggr(A a, A b) {return a+b;}
@\green{using U = z;}@
@\green{U id = 0;}@
@\green{A app(A a, U u, z s) {return a+u*s;}}@
@\green{U comp(U later, U first) {return later+first;}}@

z sz(au t) {return t ? t->s : 0;}

struct treap {
    @\yellow{K k;} \redBox{always initialize!}@
    A a; @\redBox{always initialize!}@
    A agg = a;
    @\green{U lazy = id;}@ // only for children
    @\blue{z lazy_rev = 0;}@

    z prio = rand() ^ rand(), s = 1;
    treap *l = 0, *r = 0;

    void update() { // @\red{always}@ call after changing a, l or r
        s = sz(l) + sz(r) + 1;
        agg = a;
        if(l) agg = aggr(l->agg, agg);
        if(r) agg = aggr(agg, r->agg);
    }
    void seta(A _a) {a = _a; update();}

    @\greenE{void push() \{}@ // @\red{always}@ call before visiting/changing l or r
    @\greenE\Quad\green{fe(c : {l, r})}@
    @\greenE{\Quad\Quad}\green{if(c) c->apply(lazy)}\red,\green{ c->lazy_rev ^= lazy_rev;}@
    @\greenE\Quad\green{lazy = id;}@
    @\greenE\Quad\blue{if(lazy_rev) swap(l, r)}\red,\blue{ lazy_rev = 0;}@
    @\greenE\}@

    @\greenE{void apply(U u) \{}@ // apply update on range
    @\greenE{\Quad a = app(a, u, 1);}@
    @\greenE{\Quad agg = app(agg, u, s);}@
    @\greenE{\Quad lazy = comp(u, lazy);}@
    @\greenE\}@

    @\blue{void rev() {lazy_rev ^= 1;}}@
};

using T = treap*;

pair<T, T> split(T t, B b, bool before = true) {
    if(!t) return {t, t};
    @\green{t->push();}@
    if(b-before < sz(t->l) || (b -= sz(t->l) + 1, 0)) {
    @\yellowBox{you MAY instead split at keys:}\\@
    @\yellow{if(before ? !(t->k < b) : b < t->k) }\yellowE\{@
        au [l, r] = split(t->l, b, before);
        t->l = r;
        if(l) t->update();
        return {l, t};
    } else {
        au [l, r] = split(t->r, b, before);
        t->r = l;
        if(r) t->update();
        return {t, r};
}}

T merge(T l, T r) {
    if (!l) return r;
    if (!r) return l;
    if (l->prio < r->prio) {
        @\green{l->push();}@
        l->r = merge(l->r, r);
        l->update();
        return l;
    } else {
        @\green{r->push();}@
        r->l = merge(l, r->l);
        r->update();
        return r;
}}

@\redBox{Check that t!=0 before accessing t->agg!:}@
@\opt{A agg(T t) {return t ? t->agg : __insert_neutral_A__;}}@

T extract(T& t, au a, au b, bool bex = true) { 
    // for other stuff on ranges of T, copy this, ...
    au [tl, _] = split(t, a);
    au [tm, tr] = split(_, b, bex);
    // ...do stuff with tl/tm/tr here...
    t = merge(tl, tr); // ...and replace this tl with merge(tl, tm)
    return tm;
}

void insert(T& t, T o, au b, bool before = true) { 
    au [tl, tr] = split(t, b, before);
    t = merge(merge(tl, o), tr);
}
