// Default max, add
struct Segment_tree {
	static const int RANGE = MAXN; // here
	struct Node {
		LL val, add;
		Node() {
			val = add = 0;
		}
	} t[4*RANGE];
	
	// Assume add = 0 when unite.
	Node unite(const Node &a, const Node &b) {
		Node res;
		res.val = max(a.val, b.val); // here
		return res;
	}
	void apply(LL x, Node &d, int l, int r) {
		d.val += x; // here
		d.add += x;
	}
	
	void pull(int idx) {
		t[idx] = unite(t[idx << 1], t[idx << 1 | 1]);
	}
	void push(int l, int r, int idx) {
		if (t[idx].add != 0) { // here
			int m = (l + r) >> 1;
			apply(t[idx].add, t[idx << 1], l, m);
			apply(t[idx].add, t[idx << 1 | 1], m + 1, r);
			t[idx].add = 0;
		}
	}
	
	void init(int l, int r, int idx) {
		if (l == r) {
			t[idx] = Node();
			return;
		}
		int m = (l + r) >> 1;
		init(l, m, idx << 1);
		init(m + 1, r, idx << 1 | 1);
		pull(idx);
	}	
	Node query(int ql, int qr, int l, int r, int idx) {
		if (ql <= l && r <= qr) {
			return t[idx];
		}
		LL m = (l + r) >> 1;
		push(l, r, idx);
		if (qr <= m) {
			return query(ql, qr, l, m, idx << 1);
		}
		if (ql > m) {
			return query(ql, qr, m + 1, r, idx << 1 | 1);
		}
		return unite(query(ql, qr, l, m, idx << 1), query(ql, qr, m + 1, r, idx << 1 | 1));
	}
	void update(int ql, int qr, LL v, int l, int r, int idx) {
		if (ql <= l && r <= qr) {
			apply(v, t[idx], l, r);
			return;
		}
		int m = (l + r) >> 1;
		push(l, r, idx);
		if (ql <= m) {
			update(ql, qr, v, l, m, idx << 1);
		}
		if (qr > m) {
			update(ql, qr, v, m + 1, r, idx << 1 | 1);
		}
		pull(idx);
	}
} tree;
