@\orangeBox{NTT}@  @\yellowBox{xor}@  @\greenBox{or}@  @\blueBox{and}@

@\orange{constexpr ll mod = 998244353;}@
@\orange{constexpr ll root = 3;}@

using cplx = complex<double>;

void fft(vector<@\red{cplx}@>& a, bool inverse = 0) { @\redBox{ll (not FFT)}@
	int n = sz(a);
	for (int i = 0, j = 1; j < n - 1; ++j) {
		for (int k = n >> 1; k > (i ^= k); k >>= 1);
		if (j < i) swap(a[i], a[j]);
	}
	static vector<cplx> ws(2, 1);
	for (static int k = 2; k < n; k *= 2) {
		ws.resize(n);
		cplx w = polar(1.0, acos(-1.0) / k);
		for (int i=k; i<2*k; i++) ws[i] = ws[i/2] * (i % 2 ? w : 1);
	}
	for (int s = 1; s < n; s *= 2) {
		@\orange{ll ws = powMod(root, (mod - 1) / s >> 1, mod);}@
		@\orange{if (inverse) ws = powMod(ws, mod - 2, mod);}@
		for (int j = 0; j < n; j += 2 * s) {
			@\orange{ll w = 1;}@
			for (int k = 0; k < s; k++) {
				@\orange{ll u = a[j + k], t = a[j + s + k] * w;}@
				@\orangeE{t \%= mod;}@
				@\orangeE{a[j + k] = (u + t) \% mod;}@
				@\orangeE{a[j + s + k] = (u - t + mod) \% mod;}@
				@\orangeE{w = (w * ws) \% mod;}@
				@\yellow{ll u = a[j + k], t = a[j + s + k];}@
				@\yellow{a[j + k] = u + t;}@
				@\yellow{a[j + s + k] = u - t;}@
				@\greenE{if (!inverse) \{}@
				@\green{	a[j + k] = u + t;}@
				@\green{	a[j + s + k] = u;}@
				@\greenE{\} else \{}@
				@\green{	a[j + k] = t;}@
				@\green{	a[j + s + k] = u - t;}@
				@\greenE{\}}@
				@\blueE{if (!inverse) \{}@
				@\blue{	a[j + k] = t;}@
				@\blue{	a[j + s + k] = u + t;}@
				@\blueE{\} else \{}@
				@\blue{	a[j + k] = t - u;}@
				@\blue{	a[j + s + k] = u;}@
				@\blueE{\}}@
				cplx u = a[j + k], t = a[j + s + k];
				t *= (inverse ? conj(ws[s + k]) : ws[s + k]);
				a[j + k] = u + t;
				a[j + s + k] = u - t;
				if (inverse) a[j + k] /= 2, a[j + s + k] /= 2;
	}}}
	@\orangeE{if (inverse) \{}@
	@\orange{	ll div = powMod(n, mod - 2, mod);}@
	@\orangeE{	for (ll i = 0; i < n; i++) \{}@
	@\orangeE{		a[i] = (a[i] \* div) \% mod;}@
	@\orangeE{\}\}}@
	@\yellowE{if (inverse) \{}@
	@\yellowE{	for (ll i = 0; i < n; i++) \{}@
	@\yellowE{		a[i] /= n;}@
	@\yellowE{\}\}}@
}
