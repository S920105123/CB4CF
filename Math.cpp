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
const int LIM = 100; // Double for H(n, k)
LL fac[LIM], finv[LIM];
void init_fac(LL mod) {
	fac[0] = finv[0] = 1;
	for (int i = 1; i < LIM; i++) {
		fac[i] = fac[i - 1] * i % mod;
		finv[i] = qpow(fac[i], mod - 2, mod);
	}
}
LL C(LL n, LL k, LL mod) {
	assert(n < mod && k < mod); // otherwise, use Lucas
	if (k > n || n < 0 || k < 0) return 0;
	return fac[n] * finv[k] % mod * finv[n - k] % mod;
}
LL H(LL n, LL k) {
	// n boxes, k items.
	return C(n + k - 1, k);
}
// C(n, k) % p, p is a prime, requie fac[1 ... p-1]
LL Lucas(LL n, LL k, LL p) {
	LL ans = 1;
	for (; n > 0 || k > 0; n /= p, k /= p) {
		ans = ans * C(n % p, k % p, p) % p;
	}
	return ans;
}

