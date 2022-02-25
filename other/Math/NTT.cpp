// Do NTT under N_MOD. invert=true to do iNTT.
// mod MUST be a prime, if mod = c*2^k+1, then
// p_root is any primitive root of mod
// root_pw=2^k, and n(size) MUST <= 2^k
// n MUST be power of 2.
// mod=2013265921, root_pw=1LL<<27, p_root=31

// NOTE: all input numbers should be in [0, MOD), n must be power of 2
//const LL MOD = 998244353; // here
const LL p_root = 3;
const LL root_pw = 1LL << 23;

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

LL mod_inv(LL a) {
	// for prime
	a %= MOD;
	return qpow(a, MOD - 2);
}

void ntt(vector<LL> &A, bool invert) {
	int n = A.size(); 
    LL root = qpow(p_root, (MOD-1)/root_pw);
	LL root_1 = mod_inv(root);
	for (int i = 1, j = 0; i < n; i++) {
		LL bit = n >> 1;
		for (; j & bit; bit >>= 1)
			j ^= bit;
		j ^= bit;

		if (i < j)
			swap(A[i], A[j]);
	}

	for (int len = 2; len <= n; len <<= 1) {
		LL wlen = invert ? root_1 : root;
		for (int i = len; i < root_pw; i <<= 1)
			wlen = wlen * wlen % MOD;

		for (int i = 0; i < n; i += len) {
			LL w = 1;
			for (int j = 0; j < len / 2; j++) {
				LL u = A[i+j], v = A[i+j+len/2] * w % MOD;
				A[i+j] = u + v < MOD ? u + v : u + v - MOD;
				A[i+j+len/2] = u - v >= 0 ? u - v : u - v + MOD;
				w = w * wlen % MOD;
			}
		}
	}

	if (invert) {
		LL n_1 = mod_inv(n);
		for (int i = 0; i < n; i++) {
			A[i] = A[i] * n_1 % MOD;
		}
	}
}
