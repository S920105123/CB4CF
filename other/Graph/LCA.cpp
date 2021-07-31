void init_lca(int vn) {
	// implement this by yourself
	// need: pa, din, dout, use timer as int&
//	int timer = 0; 
	dfs(1, 1, timer);
	for (int i = 1; i < LOG; i++) {
		for (int j = 1; j <= vn; j++) {
			pa[i][j] = pa[i - 1][pa[i - 1][j]];
		}
	}
}
int is_anc(int p, int v) {
	return din[p] <= din[v] && dout[v] <= dout[p];
}
int LCA(int u, int v) {
	if (is_anc(v, u)) return v;
	for (int i = LOG - 1; i >= 0; i--) {
		if (!is_anc(pa[i][v], u)) {
			v = pa[i][v];
		}
	}
	return pa[0][v];
}
