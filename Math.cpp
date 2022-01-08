LL qpow(LL a, LL pw, LL mod) {
	LL res = 1;
	a %= mod;
	while (pw) {
		if (pw & 1) res = res * a % mod;
		a = a * a % mod;
		pw >>= 1;
	}
	return res;
}
LL mod_inv(LL a, LL mod) {
	// for prime
	a %= mod;
	return qpow(a, mod - 2, mod);
}
 
/* fac, C, H */
const int LIM = 1000000; // Double for H(n, k)
const LL M_MOD = MOD;
LL fac[LIM], finv[LIM], inv[LIM];
void init_fac() {
	fac[0] = finv[0] = 1;
	for (int i = 1; i < LIM; i++) {
		fac[i] = fac[i - 1] * i % M_MOD;
		inv[i] = i == 1 ? 1 : M_MOD - M_MOD / i * inv[M_MOD % i] % M_MOD;
	}
	for (int i = 1; i < LIM; i++) {
		finv[i] = finv[i - 1] * inv[i] % M_MOD;
	}
}
LL C(LL n, LL k) {
	assert(n < M_MOD && k < M_MOD); // otherwise, use Lucas
	if (k > n || n < 0 || k < 0) return 0;
	return fac[n] * finv[k] % M_MOD * finv[n - k] % M_MOD;
}
LL H(LL n, LL k) {
	// n boxes, k items.
	return C(n + k - 1, k);
}
// C(n, k) % M_MOD, M_MOD is a prime, requie fac[1 ... M_MOD-1]
LL Lucas(LL n, LL k) {
	LL ans = 1;
	for (; n > 0 || k > 0; n /= M_MOD, k /= M_MOD) {
		ans = ans * C(n % M_MOD, k % M_MOD) % M_MOD;
	}
	return ans;
}
