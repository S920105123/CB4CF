LL find_nth_term(vector<LL> ys, LL n, LL mod) {
	// There's an unknwon polynomial P of degree at most k such that (P(0) ... P(k)) are ys[0 ... k+1]
	// Return P(n) % mod in O(k lg k), mod must be prime
	int k = (int)ys.size() - 1;
	if (n <= k) {
		return ys[n];
	}
	
	LL prod = n % mod, deno = 1;
	for (LL i = 1; i <= k; i++) {
		deno = deno * -i % mod;
		prod = prod * (n - i) % mod;
	}
	deno = (deno + mod) % mod;
	
	LL res = 0;
	for (LL i = 0; i <= k; i++) {
		ys[i] %= mod;
		res = (res + prod * mod_inv(deno * (n - i) % mod, mod) % mod * ys[i]) % mod;
		if (i < k) {
			deno = deno * mod_inv(i - k, mod) % mod * (i + 1) % mod;
		}
	}
	return (res + mod) % mod;
}
