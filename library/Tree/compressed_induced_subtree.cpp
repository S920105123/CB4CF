struct Tree {
	// input: 1-based adjacency list (each list CAN contain parent)
	// O(n lg n) init
	// query LCA / distance in O(lg n)
	// query Compressed induced tree of k vertices in O(k lg n)
public:
	int n, lg, root;
private:
	vector<int> din, dout, dep, temp;
	vector<vector<int>> pa;
	
	void dfs_init(int v, int p, int &timer, const vector<vector<int>> &G) {
		dep[v] = (v == root ? 0 : dep[p] + 1);
		din[v] = ++timer;
		pa[0][v] = p;
		for (int to : G[v]) {
			if (to != p) {
				dfs_init(to, v, timer, G);
			}
		}
		dout[v] = ++timer;
	}

public:
	void init(int _n, const vector<vector<int>> &G, int _root) {
		assert(_n > 0);
		n = _n;
		root = _root;
		lg = __lg(n) + 1;
		din.resize(n + 1);
		dout.resize(n + 1);
		dep.resize(n + 1);
		temp.resize(n + 1);
		pa.resize(lg);
		for (int i = 0; i < lg; i++) {
			pa[i].resize(n + 1);
		}
		int timer = 0;
		dfs_init(root, root, timer, G);
		for (int i = 1; i < lg; i++) {
			for (int j = 1; j <= n; j++) {
				pa[i][j] = pa[i - 1][pa[i - 1][j]];
			}
		}
	}
	int is_ancestor(int p, int v) const {
		return din[p] <= din[v] && dout[v] <= dout[p];
	}
	int LCA(int u, int v) const {
		if (is_ancestor(v, u)) return v;
		for (int i = lg - 1; i >= 0; i--) {
			if (!is_ancestor(pa[i][v], u)) {
				v = pa[i][v];
			}
		}
		return pa[0][v];
	}
	int distance(int u, int v) const {
		return dep[u] + dep[v] - 2 * dep[LCA(u, v)];
	}
	int induce(vector<int> subset, vector<int> &vertex_set, vector<int> &parent) {
		// input: a subset of vertices, which may contain duplicate vertices.
		// return: the root "r" of the compressed induced subtree T'
		// additional output: vertex_set = V(T'), parent[i] is the parent of vertex_set[i] in T' (using the labeling of T)
		// where parent[r] = r.
		
		// find LCAs
		vertex_set = subset;
		parent.clear();
		sort(subset.begin(), subset.end(), [&] (int u, int v) {
			return dout[u] < dout[v];
		});
		subset.resize(unique(subset.begin(), subset.end()) - subset.begin());
		for (int i = 1; i < subset.size(); i++) {
			vertex_set.push_back(LCA(subset[i - 1], subset[i]));
		}
		sort(vertex_set.begin(), vertex_set.end(), [&] (int u, int v) {
			return dout[u] < dout[v];
		});
		vertex_set.resize(unique(vertex_set.begin(), vertex_set.end()) - vertex_set.begin());
		for (int i = 0; i < vertex_set.size(); i++) {
			temp[vertex_set[i]] = i; // setup id
		}
		assert(vertex_set.size() <= 2 * (int)subset.size() - 1);
		
		// do dfs
		vector<int> stk;
		parent.resize(vertex_set.size());
		for (int v : vertex_set) {
			while (!stk.empty() && din[stk.back()] >= din[v]) {
				int c = stk.back();
				parent[temp[c]] = v;
				stk.pop_back();
			}
			stk.push_back(v);
		}
		assert(stk.size() == 1);
		parent[temp[stk.back()]] = stk.back();
		return stk.back();
	}
} T;
