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


// kactl
using uz = unsigned long long; // not: unsigned z!
uz modmul(uz a, uz b, uz M) {
	z ret = a * b - M * uz(1.L / M * a * b);
	return ret + M * (ret < 0) - M * (ret >= (z)M);
}
uz modpow(uz b, uz e, uz mod) {
	uz ans = 1;
	for (; e; b = modmul(b, b, mod), e /= 2)
		if (e & 1) ans = modmul(ans, b, mod);
	return ans;
}



// usual
z mulMod(z a, z b, z n) {
	z res = 0;
	while (b > 0) {
		if (b & 1) res = (a + res) % n;
		a = (a * 2) % n;
		b /= 2;
	}
	return res;
}
z powMod(z a, z b, z n) {
	z res = 1;
	while (b > 0) {
		if (b & 1) res = (a * res) % n;
		a = (a * a) % n;
		b /= 2;
	}
	return res;
}




#define time(f) [&](){\
    auto startT = chrono::high_resolution_clock::now(); \
    f \
    auto stopT = chrono::high_resolution_clock::now(); \
    return duration_cast<chrono::milliseconds>(stopT - startT).count();}()

// tested
int32_t main() {
    // z m = 1e9 + 9;
    z m = INF;

    // correctness
    for (z i = 1; i < m; i *= 2) {
        for (z j = 0; j < 10000; j++) {
            z x = (i + rand()) % m;
            z y = (i + rand()) % m;

            z a = modmul(x, y, m);
            z b = mulMod(x, y, m);
            z c = ((__uint128_t)x * y) % m;
            // z d = (x * y) % m;
            z d = c;
            if (a != b || b != c || c != d) {
                cout << "discord!" << endl;
                cout << "modmul     : " << x << " * " << y << " mod " << m << "=" << a << endl;
                cout << "mulMod     : " << x << " * " << y << " mod " << m << "=" << b << endl;
                cout << "__uint128_t: " << x << " * " << y << " mod " << m << "=" << c << endl;
                cout << "simple     : " << x << " * " << y << " mod " << m << "=" << d << endl;
                return 0;
            }
        }
    }


    // speed: modmul is 20x faster on Linus' machine
    z a = 168468431684, b = 68761641354;
    z times = 1e7;

    z total = 0;

    z timeModmul = time(
        for (z i = 0; i < times; i++) {
            total += modmul(a, (b+i), m);
        }
    );
    cout << "modmul: " << timeModmul << " ms" << endl;

    // z timeMulMod = time(
    //     for (z i = 0; i < times; i++) {
    //         total += mulMod(a, (b+i), m);
    //     }
    // );
    // cout << "mulMod: " << timeMulMod << " ms" << endl;

    z time128 = time(
        for (z i = 0; i < times; i++) {
            total += ((__uint128_t)a * (b+i)) % m;
        }
    );
    cout << "__uint128_t: " << time128 << " ms" << endl;

    z timeSimple = time(
        for (z i = 0; i < times; i++) {
            total += ((a+i) * b) % m;
        }
    );
    cout << "simple: " << timeSimple << " ms" << endl;

    if (total == 0) { // make all computations relevant
        cout << "YOU WON THE LOTTERY!" << endl;
    }
    
    /* 
    R7 4800U @ 4 GHz, WSL2 under Windows 11
    NWERC Compiler (g++, O2, no -g)
    times = 1e7

    modmul: 38 ms +- 1
    mulMod: 1846 ms
    __uint128_t: 52 ms +- 2
    simple: 0 ms (incorrect)
    */

}
