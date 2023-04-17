
struct DSU {
	// maintain a 2-coloring, where you can add constraints:
	// (u, v, c) ==> color[u] xor color[v] = c
	// cnt: number of connected component, chg: lazy tag (see get_color)
	int pa[MAXN], sz[MAXN], chg[MAXN], cnt, good;
	void init(int n) {
		cnt = n;
		good = 1;
		for (int i = 1; i <= n; i++) {
			pa[i] = i;
			sz[i] = 1;
			chg[i] = 0;
		}
	}
	int find(int x) {
		return x == pa[x] ? x : find(pa[x]);
	}
	int get_color(int x) {
		return x == pa[x] ? chg[x] : get_color(pa[x]) ^ chg[x];
	}
	void add_constraint(int x, int y, int xor_val) {
		int rx = find(x), ry = find(y);
		int cx = get_color(x), cy = get_color(y);
		if (rx == ry) {
			good &= (cx ^ cy) == xor_val;
			return;
		}
		if (sz[rx] < sz[ry]) {
			swap(x, y); swap(rx, ry); swap(cx, cy);
		} 
		cnt--;
		pa[ry] = rx;
		sz[rx] += sz[ry];
		if ((cx ^ cy) != xor_val) {
			chg[ry] ^= 1;
		}
	}
	int satisfiable() {
		return good;
	}
} U;
