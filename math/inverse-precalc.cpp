const ll mod = 1000000007, LIM = 200000;
ll* inv = new ll[LIM] - 1; inv[1] = 1;
for (z i = 2; i < LIM; i++) inv[i] = mod - (mod / i) * inv[mod % i] % mod;

// (other) idea: calc p!, its in inverse, from it all other faculty inverses, from them inverses
// from kactl