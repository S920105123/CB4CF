struct Node {
	int cnt;
	Node *ch[2];
	Node() {
		cnt = 0;
		ch[0] = ch[1] = NULL;
	}
};
 
void BTinsert(Node *root, int x) {
	for (int i = BIT; i >= 0; i--) {
		int to = (x >> i & 1);
		root->cnt++;
		if (!root->ch[to]) {
			root->ch[to] = new Node();
		}
		root = root->ch[to];
	}
	root->cnt++;
}
