const int LOG = 30;
struct Node {
	int sz;
	Node *ch[2];
	Node() {
		sz = 0;
		ch[0] = ch[1] = nullptr;
	}
	static get_size(Node *d) {
		return d == nullptr ? 0 : d->sz;
	}
	void insert(int x) {
		Node *cur = *this;
		for (int i = LOG - 1; i >= 0; i--) {
			int to = x >> i & 1;
			cur->sz++;
			if (root->ch[to] == nullptr) {
				cur->ch[to] = new Node();
			}
			cur = cur->ch[to];
		}
		root->sz++;
	}
	void find(int x) {
		Node *cur = *this;
		for (int i = LOG - 1; i >= 0; i--) {
			int to = x >> i & 1;
			if (root->ch[to] == nullptr) {
				return 0;
			}
			cur = cur->ch[to];
		}
		return 1;
	}
	int erase(int x) {
		if (!find(x)) return 0;
		Node *cur = *this;
		for (int i = LOG - 1; i >= 0; i--) {
			int to = x >> i & 1;
			cur->sz--;
			cur = cur->ch[to];
		}
		root->sz--;
		return 1;
	}
	int max_xor(int x) {
		// maximum value of x ^ (some value in trie)
		Node *cur = *this;
		for (int i = LOG - 1; i >= 0; i--) {
			int to = (x >> i & 1) ^ 1;
			if (get_size(cur->ch[to]) == 0) {
				to ^= 1;
			}
			x ^= to << i;
		}
		return x;
	}
};
