struct Lagrange {
	// Implement lagrange interpolation
	int maxd;
	vector<LL> fact, finv, inv;
//	const LL MOD = (LL) 1e9 + 7; // MOD must be a prime
	void init(int max_deg) {
		// max_deg is the maximum degree of input polynomial
		// Complexity = O(max_deg)
		maxd = max_deg;
		fact = vector<LL>(maxd + 1, 1);
		finv = vector<LL>(maxd + 1, 1);
		inv = vector<LL>(maxd + 1, 1);
		for (int i = 1; i <= maxd; i++) {
			fact[i] = fact[i - 1] * i % MOD;
			inv[i] = i == 1 ? 1 : MOD - MOD / i * inv[MOD % i] % MOD;
			finv[i] = finv[i - 1] * inv[i] % MOD;
		}
	}
	LL interpolate(vector<LL> ys, LL t) {
		// There's a polynomial P(x) of degree d = ys.size() - 1. (The leading term is x^d)
		// We know (P(0) ... P(d)), which are stored in ys[0 ... d]
		// Evaluate P(t) % MOD
		// Complexity is O(d) = O(ys.size())
		assert(ys.size() <= maxd + 1); // This line says that you cannot interpolate a polynomial of degree > maxd
		int d = (int)ys.size() - 1;
		t %= MOD;
		for (LL &y : ys) {
			y = (y % MOD + MOD) % MOD;
		}
		if (t <= d) {
			return ys[t];
		}
		
		vector<LL> pref(d + 1), suff(d + 1);
		pref[0] = t;
		for (int i = 1; i <= d; i++) {
			pref[i] = pref[i - 1] * (t - i + MOD) % MOD;
		}
		suff[d] = (t - d + MOD) % MOD;
		for (int i = d - 1; i >= 0; i--) {
			suff[i] = suff[i + 1] * (t - i + MOD) % MOD;
		}
		
		LL result = 0;
		for (int i = 0; i <= d; i++) {
			LL term = 1;
			if (i > 0) {
				term = term * pref[i - 1] % MOD;
				term = term * finv[i] % MOD;
			}
			if (i < d) {
				term = term * suff[i + 1] % MOD;
				term = term * finv[d - i] * ((d - i) % 2 ? -1 : 1) % MOD;
			}
			result = (result + ys[i] * term % MOD + MOD) % MOD;
		}
		return result;
	}
} algo;
