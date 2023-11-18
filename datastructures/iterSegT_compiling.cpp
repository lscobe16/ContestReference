#include <bits/stdc++.h>
using namespace std;

#define int long long

using z = int;
using vz = vector<z>;
using vvz = vector<vz>;
using pzz = pair<z, z>;
using vpzz = vector<pzz>;
using vvpzz = vector<vpzz>;
using vb = vector<bool>;
z INF = 1e18;

#define au auto&&
#define fe(x...) for(au x)

#define in(x...) x; [](au... a){(cin>>a, ...);}(x);
#define inv(v, n) v(n); fe(_:v){in(_)}




struct iterSegT1 {
    using A = z;
    A e = 0;
    A agg(A a, A b) {return a+b;}

    z n;
    vector<A> v;

    iterSegT1(z n): n(n), v(2 * n, e) {}
    iterSegT1(vector<A> s): n(s.size()), v(n, e) {
        v.insert(v.end(), s.begin(), s.end());
        // point set
        for (z i = n; i-- > 0;)
            v[i] = agg(v[2 * i], v[2 * i + 1]);
    }

    // point set
    void set(z i, A a) {
        v[i += n] = a;
        while (i /= 2) v[i] = agg(v[2 * i], v[2 * i + 1]);
    }
    A get(z i) {return v[i+n];}

    A query(z l, z rex) {
        A la = e, ra = e;
        for (l += n, rex += n; l < rex; l /= 2, rex /= 2) {
            if (l&1) la = agg(la, v[l++]);
            if (rex&1) ra = agg(v[--rex], ra);
        }
        return agg(la, ra);
    }

    // range apply
    // void update(z l, z rex, A a) {
    //     for (l += n, rex += n; l < rex; l /= 2, rex /= 2) {
    //         if (l&1) {v[l] = agg(v[l], a), l++;}
    //         if (rex&1) {--rex, v[rex] = agg(v[rex], a);}
    // }}

    // A query(z i) {
    //     A r = v[i += n];
    //     while(i /= 2) r = agg(r, v[i]);
    //     return r;
    // }
};


// tested on: https://judge.yosupo.jp/problem/point_add_range_sum
int32_t pointSet() {
    z in(N, Q);
    vz inv(A, N);
    iterSegT1 st(A);

    for (z i = 0; i < Q; i++) {
        bool in(u);
        if (u) {
            z in(l, rex);
            cout << st.query(l, rex) << "\n";
        } else {
            z in(p, x);
            st.set(p, st.get(p) + x);
        }
    }
}





struct iterSegT2 {
    using A = z;
    A e = 0;
    A agg(A a, A b) {return a+b;}

    z n;
    vector<A> v;

    iterSegT2(z n): n(n), v(2 * n, e) {}
    iterSegT2(vector<A> s): n(s.size()), v(n, e) {
        v.insert(v.end(), s.begin(), s.end());
        // point set
        // for (z i = n; i-- > 0;)
        //     v[i] = agg(v[2 * i], v[2 * i + 1]);
    }

    // point set
    // void set(z i, A a) {
    //     v[i += n] = a;
    //     while (i /= 2) v[i] = agg(v[2 * i], v[2 * i + 1]);
    // }
    // A get(z i) {return v[i+n];}

    // A query(z l, z rex) {
    //     A la = e, ra = e;
    //     for (l += n, rex += n; l < rex; l /= 2, rex /= 2) {
    //         if (l&1) la = agg(la, v[l++]);
    //         if (rex&1) ra = agg(v[--rex], ra);
    //     }
    //     return agg(la, ra);
    // }

    // range apply
    void update(z l, z rex, A a) {
        for (l += n, rex += n; l < rex; l /= 2, rex /= 2) {
            if (l&1) {v[l] = agg(v[l], a), l++;}
            if (rex&1) {--rex, v[rex] = agg(v[rex], a);}
    }}

    A query(z i) {
        A r = v[i += n];
        while(i /= 2) r = agg(r, v[i]);
        return r;
    }
};



// tested
int32_t main() {
    vz A = {{0, 1, 2, 3, 4, 5, 6, 7, 8, 9}};
    iterSegT2 st(A);

    cout << st.query(5) << "\n"; // 5
    cout << st.query(9) << "\n"; // 9
    st.update(2, 6, 10);
    cout << st.query(2) << "\n"; // 12
    cout << st.query(5) << "\n"; // 15
    cout << st.query(6) << "\n"; // 6
}
