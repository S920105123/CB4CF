struct DSU {
	// 1-based roll-back DSU
	struct Record {
		int x, y; // y is merged into x
	};
	int pa[MAXN], sz[MAXN];
	vector<Record> stk;
	void init(int n) {
		stk.clear();
		for (int i = 1; i <= n; i++) {
			pa[i] = i;
			sz[i] = 1;
		}
	}
	int find(int x) {
		return x == pa[x] ? x : find(pa[x]);
	}
	int merge(int x, int y) {
		x = find(x); y = find(y);
		if (x == y) {
			stk.push_back((Record){-1, -1});
			return 0;
		}
		if (sz[x] < sz[y]) swap(x, y);
		sz[x] += sz[y];
		pa[y] = x;
		stk.push_back((Record){x, y});
		return 1;
	}
	int same(int x, int y) {
		return find(x) == find(y);
	}
	void roll_back() {
		assert(!stk.empty());
		Record r = stk.back();
		stk.pop_back();
		if (r.x != -1) {
			pa[r.y] = r.y;
			sz[r.x] -= sz[r.y];
		}
	}
};
