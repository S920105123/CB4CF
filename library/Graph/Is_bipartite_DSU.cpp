struct DSU {
	// is_bip: is current graph bipartite?
	// col(v): get color of vertex v, only valid when is_bip	
	
	int is_bip;
	int pa[MAXN], sz[MAXN], add[MAXN];
	
	void init(int n) {
		is_bip = 1;
		for (int i = 0; i <= n; i++) {
			pa[i] = i;
			sz[i] = 1;
			add[i] = 0;
		}
	}
	
	int find(int x) {
		return x == pa[x] ? x : find(pa[x]); // Add compression by yourself 
	}
	int col(int x) {
		return x == pa[x] ? add[x] : (col(pa[x]) ^ add[x]);
	}
	int merge(int x, int y) {
		int c1 = col(x), c2 = col(y);
		x = find(x); y = find(y);
		if (x == y) {
			if (c1 == c2) {
				is_bip = 0;
			}
			return 0;
		}
		
		if (sz[x] < sz[y]) {
			swap(x, y);
			swap(c1, c2);
		}
		// merge
		int same = (c1 == c2);
		sz[x] += sz[y];
		pa[y] = x;
		add[y] ^= same;
		return 1;
	}
} dsu;
