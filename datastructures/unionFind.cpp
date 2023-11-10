#pragma once
#include "./header.h"

/// O(alpha(n))
struct union_find {
    vz e; //<0: -(maximum possible) height @\yellow{size}@, else: parent
    union_find(z sz) : e(sz, -1) {}
    z find(z a) {return e[a] < 0 ? a : e[a] = find(e[a]);}
    void unite(z a, z b) {
        a = find(a), b = find(b);
        if (a == b) return;
        if (e[a] > e[b]) swap(a, b);
        e[a] -= @\yellow{e[a] == }@e[b]; @\yellowBox{for storing+uniting by size(slower)}@
        e[b] = a;
    }
    bool same(z a, z b) {return find(a) == find(b);}
    @\yellow{z sz(z a) {return -e[find(a)];}}@
};
