// Default (add, set, min) = (update, point_update, query)
struct Segment_tree {
//	static const int RANGE = MAXN; // here
//	static const int NO_TAG = 0; // here
	struct Node {
		LL val, tag;
		Node() { // here
			// val = minv, tag = add_tag
			val = 0;
			tag = NO_TAG;
		}
	} t[4*RANGE];
	
	// Assume add = 0 when unite.
	Node unite(const Node &a, const Node &b) {
		Node res;
		res.val = min(a.val, b.val); // here
		return res;
	}
	void apply(LL x, Node &d, int l, int r) {
		d.val += x; // here
		d.tag += x;
	}
	
	void pull(int idx) {
		t[idx] = unite(t[idx << 1], t[idx << 1 | 1]);
	}
	void push(int l, int r, int idx) {
		if (t[idx].tag != NO_TAG) { // watch out NO_TAG
			int mid = (l + r) >> 1;
			apply(t[idx].tag, t[idx << 1], l, mid);
			apply(t[idx].tag, t[idx << 1 | 1], mid + 1, r);
			t[idx].tag = NO_TAG;
		}
	}
	
	void init(int l, int r, int idx) {
		t[idx].tag = NO_TAG;
		if (l == r) {
			t[idx] = Node();
			return;
		}
		int mid = (l + r) >> 1;
		init(l, mid, idx << 1);
		init(mid + 1, r, idx << 1 | 1);
		pull(idx);
	}	
	Node query(int ql, int qr, int l, int r, int idx) {
		if (ql <= l && r <= qr) {
			return t[idx];
		}
		int mid = (l + r) >> 1;
		push(l, r, idx);
		if (qr <= mid) {
			return query(ql, qr, l, mid, idx << 1);
		}
		if (ql > mid) {
			return query(ql, qr, mid + 1, r, idx << 1 | 1);
		}
		return unite(query(ql, qr, l, mid, idx << 1), query(ql, qr, mid + 1, r, idx << 1 | 1));
	}
	void point_update(int q, LL v, int l, int r, int idx) {
		if (l == r) {
			t[idx].val = v; // here
			return;
		}
		push(l, r, idx);
		int mid = (l + r) >> 1;
		if (q <= mid) {
			point_update(q, v, l, mid, idx << 1);
		}
		else {
			point_update(q, v, mid + 1, r, idx << 1 | 1);
		}
		pull(idx);
	}
	void update(int ql, int qr, LL v, int l, int r, int idx) {
		if (ql <= l && r <= qr) {
			apply(v, t[idx], l, r);
			return;
		}
		int mid = (l + r) >> 1;
		push(l, r, idx);
		if (ql <= mid) {
			update(ql, qr, v, l, mid, idx << 1);
		}
		if (qr > mid) {
			update(ql, qr, v, mid + 1, r, idx << 1 | 1);
		}
		pull(idx);
	}
} tree;
