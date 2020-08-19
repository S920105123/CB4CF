// 2^LOG <= MAXN for safety 
int n, timer, st[MAXN], ed[MAXN], dep[MAXN], pa[LOG][MAXN];
vector<int> G[MAXN];

void lca_dfs(int v, int p, int d) { // NOT API
	st[v] = ++timer;
	pa[0][v] = p; 
	dep[v] = d;
	for (int to : G[v]) {
		if (to != p) {
			lca_dfs(to, v, d + 1);
		}
	}
	ed[v] = timer;
}

int is_anc(int p, int v) { // API
	return st[p] <= st[v] && ed[v] <= ed[p];
}

int get_lca(int u, int v) { // API
	if (is_anc(u, v)) return u;
	for (int i = LOG - 1; i >= 0; i--) {
		if (!is_anc(pa[i][u], v)) {
			u = pa[i][u];
		}
	}
	return pa[0][u];
}

int level_anc(int v, int k) {
	// k level ancestor of v, -1 if not exist
	if (k > dep[v]) return -1;
	for (int i = LOG - 1; i >= 0; i--) {
		if (k >> i & 1) {
			v = pa[i][v];
		}
	}
	return v;
}

void init_lca(int root) { // Call this
	timer = 0;
	lca_dfs(root, root, 0);
	for (int i = 1; i < LOG; i++) {
		for (int j = 1; j <= n; j++) {
			pa[i][j] = pa[i - 1][pa[i - 1][j]];
		}
	}
}
