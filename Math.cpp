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
 
void add(LL &x, LL y) {
	x += y;
	if (x >= MOD) {
		x -= MOD;
	}
}
 
/* fac, C, H */
const int LIM = 1000005; // Double for H(n, k)
LL fac[LIM], finv[LIM], inv[LIM];
void init_fac() {
	fac[0] = finv[0] = 1;
	for (int i = 1; i < LIM; i++) {
		fac[i] = fac[i - 1] * i % MOD;
		inv[i] = i == 1 ? 1 : MOD - MOD / i * inv[MOD % i] % MOD;
		finv[i] = finv[i - 1] * inv[i] % MOD;
	}
}
LL C(LL n, LL k) {
	assert(n < MOD && k < MOD); // otherwise, use Lucas
	if (k > n || n < 0 || k < 0) return 0;
	return fac[n] * finv[k] % MOD * finv[n - k] % MOD;
}
LL H(LL n, LL k) {
	// n boxes, k items.
	return C(n + k - 1, k);
}
// C(n, k) % M_MOD, M_MOD is a prime, requie fac[1 ... M_MOD-1]
LL Lucas(LL n, LL k) {
	LL ans = 1;
	for (; n > 0 || k > 0; n /= MOD, k /= MOD) {
		ans = ans * C(n % MOD, k % MOD) % MOD;
	}
	return ans;
}

