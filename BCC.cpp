int bcc_cnt, dep[MAXN], low[MAXN], bccid[MAXN];
vector<int> stk;
vector<Edge> G[MAXN];

void bcc_dfs(int v, int p, int d) {
	vis[v] = 1;
	low[v] = dep[v] = d;
	int last = stk.back(); // ********* PUSH -1 BEFORE DFS
	stk.push_back(v);
	for (Edge e : G[v]) {
		int to = e.to;
		if (to == p) continue; // **** If multiple edges, check its id.
		if (vis[to] == 1) {
			low[v] = min(low[v], dep[to]);
		}
		else if (vis[to] == 0) {
			bcc_dfs(to, v, d + 1);
			low[v] = min(low[v], low[to]);
		}
	}
	
	if (v == p || low[v] == dep[v]) {
		++bcc_cnt;
		while (stk.back() != last) {
			bccid[stk.back()] = bcc_cnt;
			stk.pop_back();
		}
	}
	vis[v] = 2;
}
