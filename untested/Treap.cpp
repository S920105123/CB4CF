struct Treap {
	int sz, key, pri, tag;
	Treap *l, *r;
	Treap(int _key) {
		key = _key; sz = 1;
		pri = rand(); l = r = NULL; tag = 0;
	}
};
void push(Treap * a) {
	if (a->tag) {
		swap(a->l, a->r);
		if (a->l) a->l->tag ^= 1;
		if (a->r) a->r->tag ^= 1;
		a->tag = 0;
	}
}
int Size(Treap *a) { return a ? a->sz : 0; }
void pull(Treap *a) {
	a->sz = Size(a->l) + Size(a->r) + 1;
}

Treap* merge(Treap *a, Treap *b) {
	if (!a || !b) return a ? a : b;
	if (a->pri > b->pri) {
		push(a);
		a->r = merge(a->r, b);
		pull(a);
		return a;
	} else {
		push(b);
		b->l = merge(a, b->l);
		pull(b);
		return b;
	}
}
void split(Treap *t, int k, Treap *&a, Treap *&b) {
	// Split by size. First k elements <-> in *a
	if(!t) { a = b = NULL; return; }
	push(t);
	if(Size(t->l) + 1 <= k) {
		a = t;
		split(t->r, k - Size( t->l ) - 1, a->r , b );
		pull(a);
	} else {		b = t;
		split(t->l, k, a, b->l);
		pull( b );
	}
}
void split2(Treap *t, int k, Treap *&a, Treap *&b ) {
	// Split by key. Key < k <-> in *a, when used as a BST
	if (!t) { a = b = NULL; return; }
	push(t);
	if (t->key < k) {
		a = t;
		split2(t->r, k, a->r, b);
		pull(a);
	} else {
		b = t;
		split2(t->l, k, a, b->l);
		pull(b);
	}
}

