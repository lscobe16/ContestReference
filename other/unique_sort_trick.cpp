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

#define in(x...) x; [](au... a){((cin>>a), ...);}(x);
#define inv(v, n) v(n); fe(_:v){in(_)}
#define dbg(x) cerr<<__LINE__<<": \t"#x" = "<<(x)<<"\n";

au operator-(ostream& o, au t) {return o << t << ' ';}
au operator+(ostream& o, au t) {return o << t << '\n';}

#define time(f...) [&](){\
    auto startT = chrono::high_resolution_clock::now(); \
    f; \
    auto stopT = chrono::high_resolution_clock::now(); \
    return chrono::duration_cast<chrono::milliseconds>(stopT - startT).count();}()




vz uniques_hashtable(vz &A) {
    unordered_map<z,z> H;
    fe(a:A) H[a]++;
    vz uniques;
    fe([a, cnt] : H) {
        if (cnt == 1) uniques.push_back(a);
    }
    return uniques;
}

vz uniques_map(vz &A) {
    map<z,z> H;
    fe(a:A) H[a]++;
    vz uniques;
    fe([a, cnt] : H) {
        if (cnt == 1) uniques.push_back(a);
    }
    return uniques;
}

vz uniques_sort(vz &A) { // incl copy for now
    z n = A.size();
    if (n == 1) return A;
    vz B = A;
    sort(B.begin(), B.end());
    vz uniques;
    for (z i = 0; i < n-1; i++) {
        while (i<n-1 && B[i] == B[i+1]) i++;
        if (i == n-1) break;
        if (i == 0 || B[i-1] != B[i]) uniques.push_back(B[i]);
    }
    if (B[n-2] != B[n-1]) uniques.push_back(B[n-1]);
    return uniques;
}



int32_t main() {
    z n = 5e5, p = 1e9;

    vz A;
    for (z i = 0; i < n; i++) {
        A.push_back(rand() % p);
    }

    dbg(A.size())
    dbg(RAND_MAX) // max values

    dbg(time(uniques_hashtable(A)));
    dbg(time(uniques_map(A)));
    dbg(time(uniques_sort(A)));
}
