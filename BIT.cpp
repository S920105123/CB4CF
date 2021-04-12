struct BIT {
//	const int RANGE = MAXN;
	LL c[RANGE];
	void init(int n) {
		fill(c, c + n + 1, 0);
	}
	void add(int p, LL v) {
		while (p < RANGE) {
			c[p] += v;
			p += p & -p;
		}
	}
	LL get(int p) {
		LL res = 0;
		while (p) {
			res += c[p];
			p -= p & -p;
		}
		return res;
	}
	LL RSQ(int l, int r) {
		if (l > r) return 0;
		return get(r) - get(l - 1);
	}
} tree;
