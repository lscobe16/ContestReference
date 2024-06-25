#define assOp(T, op) T operator op##=(T o) {return *this = *this op o;}
#define assOps(T) assOp(T,+) assOp(T,-) assOp(T,*) assOp(T,/)

z MOD = 1e9+7; //Muss in main.cpp richtig initialisiert werden. Kann verändert werden (Vorsicht damit!)

z modmul(z a, z b, z M=MOD) {
    return (__int128)a * b % M;
}

z modpow(z b, z e, z M=MOD) {
    if (e < 0) { // for negative exponents
        assert(b);
        e %= M-1;
        e += M-1;
    }
    z x = 1;
    for(; e; b = modmul(b, b, M), e /= 2)
        if (e & 1) x = modmul(x, b, M);
    return x;
}

struct mz {
    z a;
    mz(z a = 0) : a(a % MOD + MOD * (a < 0)) {}
    mz operator+(mz o) {
        return a + o.a;
    }
    mz operator-() {
        return -a;
    }
    mz operator-(mz o) {
        return *this + -o;
    }
    mz operator*(mz o) {
        return modmul(a, o.a, MOD);
    }
    /// b >= 0 or a != 0
    mz operator^(z b) {
        return modpow(a, b, MOD);
    }
    mz operator/(mz o) {
        return *this * (o^-1);  //Achtung: dafür muss modpow mit neg. Zahlen umgehen können!
    }
    assOps(mz)
};

struct mfr {
    mz p, q;
    mfr(mz p=0, mz q=1): p(p), q(q) {}
    mfr(z p): mfr(p, 1) {}
    mfr operator*(mfr o) {
        return {p * o.p, q * o.q};
    }
    mfr operator+(mfr o) {
        return {p * o.q + q * o.p, q * o.q};
    }
    mfr operator-() {
        mfr a(-p, q);
        return a;
    }
    mfr operator-(mfr o) {
        return *this + -o;
    }
    /// b >= 0 or p != 0
    mfr operator^(z b) {
        return b < 0 ? mfr{q, p} ^ -b : mfr{p ^ b, q ^ b};
    }
    /// o.p != 0
    mfr operator/(mfr o) {
        return *this * (o^-1);
    }
    assOps(mfr)

    z asZ() {
        return (p/q.a).a;
    }
    static mfr fromDoubleString(string d) {
        z i = d.find('.');
        d.erase(i, 1);
        return {stoll(d), mz(10)^(d.size()-i)};
    }

    mfr reduce() {
        if (!p.a) return {0, 1};
        z g = gcd(p.a, q.a);
        return {p/g, q/g};
    }
};

au operator<<(ostream& o, mfr t) {
    auto x = t.reduce();
    return o << x.p.a << "/" << x.q.a;
}
