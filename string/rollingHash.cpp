z M = 1'500'000'001; // 1'600'000'009, 1'700'000'009
z Q = 101; // 29, 53, 257, 1009, 65'537 \in [max(alphabet) /*TODO: +1 or +2?*/, M]
char A = 'A';
@\green{template<z M, z Q>}@  @\greenBox{multiple different bases}@
struct Hasher { // bigger powers are left
	vz power = {1}, pref = {0};
	Hasher(string s) {
		fe (x:s) {
			power.push_back(power.back() * Q % M);
			pref.push_back((pref.back() * Q % M + (x-A+1)) % M);
	}}

	z hash(z l, z rex) {	// Berechnet hash(s[l..rex)).
		return (pref[rex] - power[rex-l] * pref[l] % M + M) % M;
	}
};
