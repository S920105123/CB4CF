struct DSU {
	int pa[MAXN], sz[MAXN];
	void init(int n) {
		for (int i = 0; i <= n; i++) {
			pa[i] = i;
			sz[i] = 1;
		}
	}
	int find(int x) {
		return x == pa[x] ? x : pa[x] = find(pa[x]);
	}
	int merge(int x, int y) {
		x = find(x); y = find(y);
		if (x == y) return 0;
		if (sz[x] < sz[y]) swap(x, y);
		sz[x] += sz[y];
		pa[y] = x;
		return 1;
	}
} dsu;
