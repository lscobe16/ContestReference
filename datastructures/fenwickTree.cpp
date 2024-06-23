struct fenwick { @\greenBox{e.g. z pot(z x) = 1 << x;}@
    vz v;
    fenwick(z n) : v(n+1) {}

    void add(z i, z delta) { // i in [0, n)
        for (i++; i < v.size(); @\green{delta *= pot(i&-i),}@ i += i&-i) v[i] += delta;
    }

    z prefix_sum(z i) { // rex in [0, n]
        z sum = 0 @\green{, dist = 0}@;
        for (; i > 0; @\green{dist += i&-i,}@ i -= i&-i) sum += v[i] @\green{* pot(dist)}@;
        return sum;
}};
