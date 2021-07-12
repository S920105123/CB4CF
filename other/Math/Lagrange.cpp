LL find_nth_term(vector<LL> ys, LL n, LL mod) {
	// There's an unknwon polynomial P of degree at most k such that (P(0) ... P(k)) are ys[0 ... k+1]
	// Return P(n) % mod in O(k lg k), mod must be prime
	int k = (int)ys.size() - 1;
	n %= mod;
	for (LL &y : ys) {
		y = (y % mod + mod) % mod;
	}
	if (n <= k) {
		return ys[n];
	}
	
	LL prod = 1, deno = 1;
	for (LL i = 1; i <= k; i++) {
		deno = deno * -i % mod;
		prod = prod * (n - i) % mod;
	}
	prod = prod * mod_inv((deno + mod) % mod, mod) % mod;
	
	LL res = 0;
	for (LL i = 0; i <= k; i++) {
		res = (res + prod * ys[i]) % mod;
		if (i < k) {
			prod = prod * mod_inv((i + 1) * (n - i - 1) % mod, mod) % mod;
			prod = prod * (i - k + mod) % mod * (n - i) % mod;
		}
	}
	return res;
}
