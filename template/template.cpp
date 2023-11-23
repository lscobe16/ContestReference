#include <bits/stdc++.h>
using namespace std;

#define int long long

using z = int;
using vz = vector<z>;
@\opt{using vvz = vector<vz>;}@
@\optE{// auch mit\ \ pzz=pair<z,z>\ \ und\ \ ld=long double\ \ (mit Alt+J)}@

#define au auto&&
#define fe(x...) for(au x)

// Usage: z in(n, m)    and    vz inv(a, n)
#define in(x...) x; [](au... a){((cin>>a), ...);}(x);
#define inv(v, n) v(n); fe(_:v){in(_)}

@\opt{au pr = cout;}@
au operator-(ostream& o, au t) {return o << t << ' ';}
au operator+(ostream& o, au t) {return o << t << '\n';}

@\opt{z INF = 1e18;}@ //max z = ca. 9e18

@\optE{\#define dbg(x) (cerr<<\_\_LINE\_\_<<": \textbackslash}\optE{t"\#x}\opt{" = ")+(x);}@

int32_t main() {
    @\opt{cin.tie(0)->sync_with_stdio(0);}@
    @\opt{cout.precision(16);}@
    @\opt{cin.exceptions(cin.failbit);}@ // some WAs ~> RTE

}
