struct BIT{
	vector<LL> C;
	void init(int n) {
		C = vector<LL>(n + 1, 0);
	}
	void add(int p, LL v) {
		while (p < C.size()) {
			C[p] += v;
			p += p & -p;
		}
	}
	LL get(int p) {
		LL res = 0;
		while (p) {
			res += C[p];
			p -= p & -p;
		}
		return res;
	}
	LL RSQ(int l, int r) {
		return (l > r ? 0 : get(r) - get(l - 1));
	}
	int search(LL t) {
		// last p, A[1] + A[2] + ... + A[p] < t.
		// A is the represented array. p can be 0.
		// CONDITION: each int in A >= 0
		LL cur = 0;
		int pref = 0, n = C.size() - 1;
		for (int i = (1 << __lg(n)); i >= 1; i >>= 1) {
			if (pref + i <= n && cur + C[pref + i] < t) {
				cur += C[pref + i];
				pref += i;
			}
		}
		return pref;
	}
} tree;

