// Find S(n, k) for k = 0, 1, ..., n in O(n lg n)
vector<LL> Stirling_number_of_second_kind(int n) {
	vector<LL> A(n + 1), B(n + 1);
	for (int i = 0; i <= n; i++) {
		A[i] = qpow(i, n) * finv[i] % MOD;
		B[i] = ((i & 1 ? MOD - 1 : 1)) * finv[i] % MOD;
	}
	return NTT::mul(A, B);
}
