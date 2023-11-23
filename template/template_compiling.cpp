#include <bits/stdc++.h>
using namespace std;

#define int long long

using z = int;
using vz = vector<z>;
using vvz = vector<vz>;

using pzz = pair<z,z>;
using vpzz = vector<pzz>;
using vvpzz = vector<vpzz>;

using ld = long double;
using vld = vector<ld>;
using vvld = vector<vld>;


#define au auto&&
#define fe(x...) for(au x)

// Usage: z in(n, m)    and    vz inv(a, n)
#define in(x...) x; [](au... a){((cin>>a), ...);}(x);
#define inv(v, n) v(n); fe(_:v){in(_)}

au pr = cout;
au operator-(ostream& o, au t) {return o << t << ' ';}
au operator+(ostream& o, au t) {return o << t << '\n';}

z INF = 1e18; //max z = ca. 9e18

#define dbg(x) (cerr<<__LINE__<<": \t"#x" = ")+(x);

/*
int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    cout.precision(16);
    cin.exceptions(cin.failbit); // some WAs ~> RTE

}
*/