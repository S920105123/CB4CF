static const int MAXL=200005,SIGMA=26; // MAXL: sum of length in dictionary
// link: suffix link, next: DFA link, n: # of nodes, tag: ID of str ends here
// next and link always exist, others exist iff values != -1.
// nocc: next occurrence, first node with tag != -1 along suffix link
int n, dep[MAXL], link[MAXL], next[MAXL][SIGMA];
int trie[MAXL][SIGMA], tag[MAXL], nocc[MAXL];

int new_node(int p) {
	// Add you init if recording more values.
	dep[n] = n == 0 ? 0 : dep[p] + 1;
	link[n] = tag[n] = nocc[n] = -1;
	for (int i = 0; i < SIGMA; i++) {
		next[n][i] = 0;
		trie[n][i] = -1;
	}
	return n++;
}
void build(vector<string> &dict) {
	// Some init should be written in new_node, O(N*SIGMA).
	n = 0;
	new_node(0);
	for (int i = 0; i < dict.size(); i++) {
		int v = 0;
		for (char ch : dict[i]) {
			int to = ch - 'a'; // CHANGE THIS !!
			if (trie[v][to] == -1) {
				trie[v][to] = next[v][to] = new_node(v);
			}
			v = trie[v][to];
		}
		tag[v] = i;
	}
	
	queue<int> Q;
	link[0] = 0;
	Q.push(0);
	while (!Q.empty()) {
		int v = Q.front(); Q.pop();
		for (int to = 0; to < SIGMA; to++) {
			if (trie[v][to] != -1) {
				int u = trie[v][to];
				link[u] = v == 0 ? 0 : next[link[v]][to];
				nocc[u] = tag[link[u]] != -1 ? link[u] : nocc[link[u]];
				for (int j = 0; j < SIGMA; j++) {
					if (trie[u][j] == -1) {
						next[u][j] = next[link[u]][j];
					}
				}
				Q.push(u);
			}
		}
	}
}
