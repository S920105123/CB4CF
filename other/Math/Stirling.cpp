// Find S(n, k) for k = 0, 1, ..., n in O(n lg n)
vector<LL> Stirling_number_of_second_kind(int n) {
	int sz = 1;
	while (sz < 2 * n + 1) {
		sz *= 2;
	}
	vector<LL> A(sz), B(sz);
	for (int i = 0; i <= n; i++) {
		A[i] = qpow(i, n) * finv[i] % MOD;
		B[i] = ((i & 1 ? MOD - 1 : 1)) * finv[i] % MOD;
	}
	ntt(A, 0); ntt(B, 0);
	for (int i = 0; i < sz; i++) {
		A[i] = A[i] * B[i] % MOD;
	}
	ntt(A, 1);
	A.resize(n + 1);
	for (int i = 0; i <= n; i++) {
		if (A[i] < 0) {
			A[i] += MOD;
		}
	}
	return A;
}

