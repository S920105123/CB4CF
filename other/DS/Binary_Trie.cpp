struct BTrie {
//	static const int LOG = 30;
//	static const int MAXT = LOG * MAXN;
	
	struct Node {
		int sz;
		Node *ch[2];
		Node() {
			sz = 0;
			ch[0] = ch[1] = nullptr;
		}
	};
	
	int ptr;
	Node *root;
	Node N[MAXT];
	
	Node* new_node() {
		N[ptr] = Node();
		return &N[ptr++];
	}
	
	BTrie() { root = NULL; ptr = 0; }
	
	void init() {
		ptr = 0;
		root = new_node();
	}
	
	void insert(int key) {
		Node *cur = root;
		for (int i = LOG - 1; i >= 0; i--) {
			int to = key >> i & 1;
			cur->sz++;
			if (cur->ch[to] == nullptr) {
				cur->ch[to] = new_node();
			}
			cur = cur->ch[to];
		}
		cur->sz++;
	}
	
	int find(int key) {
		Node *cur = root;
		for (int i = LOG - 1; i >= 0; i--) {
			int to = key >> i & 1;
			if (cur->ch[to] == nullptr) {
				return 0;
			}
			cur = cur->ch[to];
		}
		return 1;
	}
	
	int erase(int key) {
		Node *cur = root;
		for (int i = LOG - 1; i >= 0; i--) {
			int to = key >> i & 1;
			cur->sz--;
			cur = cur->ch[to];
		}
		cur->sz--;
		return 1;
	}
	
	int min_xor(int key) {
		// minimum value of key ^ (some value in trie)
		int mask = key;
		Node *cur = root;
		assert(get_size(root) > 0);
		for (int i = LOG - 1; i >= 0; i--) {
			int to = key >> i & 1;
			if (get_size(cur->ch[to]) == 0) {
				to ^= 1;
			}
			mask ^= to << i;
			cur = cur->ch[to];
		}
		return mask;
	}
	
	int size() {
		return get_size(root);
	}
	
	private:
	int get_size(Node *d) {
		return d == nullptr ? 0 : d->sz;
	}
};
