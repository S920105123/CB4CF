// Every structure change should be done by merge-split.
// Pushdown is really hard to implement and has huge constant, try your best to avoid it.
// mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
struct Treap {
	int sz, key, pri;
	Treap *l, *r;
	Treap(int _key) {
		key = _key; sz = 1;
		pri = rng(); l = r = NULL;
	}
	Treap(Treap *t) {
		assert(t != NULL);
		*this = *t;
	}
};
int Size(Treap *a) { return a ? a->sz : 0; }
void pull(Treap *a) {
	a->sz = Size(a->l) + Size(a->r) + 1;
}

vector<Treap> mem;
Treap* new_node(int key) {
	mem.push_back(Treap(key));
	return &mem.back();
}
Treap* new_node(Treap *t) {
	mem.push_back(Treap(t));
	return &mem.back();
}

Treap* merge(Treap *a, Treap *b) { // When new, also copy priority
	if (!a || !b) return a ? (new_node(a)) : (new_node(b));
	Treap *t;
	if (a->pri > b->pri) {
		t = new_node(a);
		t->r = merge(t->r, b);
		pull(t);
		return t;
	}
	else {
		t = new_node(b);
		t->l = merge(a, t->l);
		pull(t);
		return t;
	}
}
void split(Treap *t, int k, Treap *&a, Treap *&b) {
	// Split by key. Key < k <==> in *a
	if (!t) { a = b = NULL; return; }
	t = new_node(t);
	if (t->key < k) {
		a = t;
		split(t->r, k, a->r, b);
		pull(a);
	}
	else {
		b = t;
		split(t->l, k, a, b->l);
		pull(b);
	}
}
void split2(Treap *t, int k, Treap *&a, Treap *&b) {
	// Split by size. First k numbers <-> in *a
	if (!t) { a = b = NULL; return; }
	t = new_node(t);
	if (Size(t->l) < k) {
		a = t;
		split2(t->r, k - Size(t->l) - 1, a->r, b);
		pull(a);
	}
	else {
		b = t;
		split2(t->l, k, a, b->l);
		pull(b);
	}
}
