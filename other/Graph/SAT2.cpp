int N, sid[MAXV*2]; // all 1-based
bool vis[MAXV*2], sol[MAXV]; // 1 if i is true
vector<int> stk, G[MAXV*2], Gr[MAXV*2];
void init(int _N) {
	N = _N; // number of variable 
	for (int i = 0; i <= 2 * N; i++) {
		G[i].clear();
		Gr[i].clear();
	}
}
int get_not(int x) {
	return x <= N ? x + N : x - N; // Note when 0-based
}
void add_edge(int x, int y) {
	G[x].push_back(y);
	Gr[y].push_back(x);
}
void add_or(int x, int y) {
	add_edge(get_not(x), y);
	add_edge(get_not(y), x);
}
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
bool solve() {
	int V = 2 * N;
	stk.clear();
	fill(vis, vis + V + 1, 0);
	fill(sid, sid + V + 1, 0);
	for (int i = 1; i <= V; i++) {
		if (!vis[i]) {
			dfs(i);
		}
	}
	
	int cnt = 0;
	for (int i = (int) stk.size() - 1; i >= 0; i--) {
		if (sid[stk[i]] == 0) {
			rdfs(stk[i], ++cnt);
		}
	}
	
	for (int i = 1; i <= N; i++) {
		if (sid[i] == sid[i + N]) return false;
		sol[i] = (sid[i + N] < sid[i]);
	}
	return true;
}
