// T: the adjacency of a tree rooted at vertex 1
// base: base for hash, 2 <= base < MOD
// return hash of T % (1e9 + 7)
LL get_hash(const vector<vector<int>> &T, LL base) {
	int n = T.size() - 1;
	const LL MOD = (LL)1e9 + 7;
	
	vector<int> sz(n + 1);
	vector<LL> pw(2 * n - 1, 1), hash(n + 1);
	for (int i = 1; i < (int)pw.size(); i++) {
		pw[i] = pw[i - 1] * base % MOD;
	}
	
	function<LL(int, int)> dfs = [&] (int v, int p) {
		vector<pair<LL, int>> child;
		sz[v] = 1;
		for (int to : T[v]) {
			if (to != p) {
				dfs(to, v);
				child.push_back(make_pair(hash[to], sz[to]));
				sz[v] += sz[to];
			}
		}
		
		LL res = 0;
		sort(child.begin(), child.end());
		for (auto c : child) {
			res = (res * pw[2 * c.second] + c.first * base + 1) % MOD;
		}
		return hash[v] = res;
	};
	return dfs(1, 1);
}
