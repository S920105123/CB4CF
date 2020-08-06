// SCC are indexed in topological order, (u, v) exist only for u < v.
int n, m, vis[MAXN], sid[MAXN], scc_sz[MAXN];
vector<int> stk, G[MAXN], Gr[MAXN];
void dfs(int v) {
	vis[v] = 1;
	for (int to : G[v]) {
		if (!vis[to]) {
			dfs(to);
		}
	}
	stk.push_back(v);
}
void rdfs(int v, int root) {
	sid[v] = root;
	for (int to : Gr[v]) {
		if (sid[to] == 0) {
			rdfs(to, root);
		}
	}
}
int find_SCC() {
	stk.clear();
	fill(vis, vis + n + 1, 0);
	fill(sid, sid + n + 1, 0);
	for (int i = 1; i <= n; i++) {
		if (!vis[i]) {
			dfs(i);
		}
	}
	
	int cnt = 0;
	for (int i = (int) stk.size() - 1; i >= 0; i--) {
		if (sid[stk[i]] == 0) {
			rdfs(stk[i], ++cnt);
		}
		scc_sz[sid[stk[i]]]++;
	}
	
	return cnt;
}
