LL qpow(LL a, LL pw) {
	LL res = 1;
	a %= MOD;
	while (pw) {
		if (pw & 1) res = res * a % MOD;
		a = a * a % MOD;
		pw >>= 1;
	}
	return res;
}
 
/* fac, C, H */
const int LIM = 1000005; // Double for H(n, k)
LL fac[LIM], finv[LIM];

void init() {
	fac[0] = finv[0] = 1;
	for (int i = 1; i < LIM; i++) {
		fac[i] = fac[i - 1] * i % MOD;
		finv[i] = qpow(fac[i], MOD - 2);
	}
}

LL C(LL n, LL k) {
	return fac[n] * finv[k] % MOD * finv[n - k] % MOD;
}

LL H(LL n, LL k) {
	// n boxes, k items.
	return C(n + k - 1, k);
}

/*
pair<LL, LL> ext_gcd( LL a, LL b) {
	if (b == 0) return make_pair(1, 0);
    if (a % b == 0) return make_pair(0, 1);
    pair<LL, LL> t = ext_gcd(b, a % b);
    return make_pair( t.second, t.first - a / b * t.second);
}
LL mod_inv(LL x, LL mod) { // gcd(x,mod) must be 1
    return (exd_gcd(x,mod).first % mod + mod) % mod;
}
*/
