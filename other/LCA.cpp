//const int MAXN = 100005, LOG = 19; // 2^LOG <= MAXN for safety 
int n, timer, st[MAXN], ed[MAXN], pa[LOG][MAXN];
vector<int> G[MAXN];

int is_anc(int p, int v) {
	return st[p] <= st[v] && ed[v] <= ed[p];
}

int get_lca(int u, int v) {
	if (is_anc(u, v)) return u;
	for (int i = LOG - 1; i >= 0; i--) {
		if (!is_anc(pa[i][u], v)) {
			u = pa[i][u];
		}
	}
	return pa[0][u];
}

void lca_dfs(int v, int p) {
	st[v] = ++timer;
	pa[0][v] = p; 
	for (int to : G[v]) {
		if (to != p) {
			lca_dfs(to, v);
		}
	}
	ed[v] = timer;
}

void init() {		
	timer = 0;
	lca_dfs(1, 1);
	for (int i = 1; i < LOG; i++) {
		for (int j = 1; j <= n; j++) {
			pa[i][j] = pa[i - 1][pa[i - 1][j]];
		}
	}
}
