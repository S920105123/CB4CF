//#pragma GCC optimize ("O3", "unroll-loops")
//#pragma GCC target ("avx2")
//#pragma comment(linker, "/stack:200000000")
//#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
#include <bits/stdc++.h>
#define LL long long
#define PII pair<int, int>
#define PLL pair<LL, LL>
#define all_of(v) (v).begin(), (v).end()
#define fi first
#define se second
using namespace std;

struct Rooted_tree {
	// input: 1-based adjacency list (each list CAN contain parent)
	// O(n lg n) init
	// query LCA / distance in O(lg n)
	// query Compressed induced tree of k vertices in O(k lg n)
private:
	int n, lg, root;
	vector<int> din, dout, dep, temp;
	vector<vector<int>> pa;
	vector<int> *G;
	
	void dfs_init(int v, int p, int &timer) {
		dep[v] = (v == root ? 0 : dep[p] + 1);
		din[v] = ++timer;
		pa[0][v] = p;
		for (int to : G[v]) {
			if (to != p) {
				dfs_init(to, v, timer);
				dep[to] = dep[v] + 1;
			}
		}
		dout[v] = ++timer;
	}

public:
	void init(int _n, vector<int> *_G, int _root) {
		assert(_n > 0);
		G = _G;
		n = _n;
		root = _root;
		lg = __lg(n);
		din.resize(n + 1);
		dout.resize(n + 1);
		dep.resize(n + 1);
		temp.resize(n + 1);
		pa.resize(lg);
		for (int i = 0; i < lg; i++) {
			pa[i].resize(n + 1);
		}
		int timer = 0;
		dfs_init(root, root, timer);
		for (int i = 1; i < lg; i++) {
			for (int j = 1; j <= n; j++) {
				pa[i][j] = pa[i - 1][pa[i - 1][j]];
			}
		}
	}
	int is_ancestor(int p, int v) {
		return din[p] <= din[v] && dout[v] <= dout[p];
	}
	int LCA(int u, int v) {
		if (is_ancestor(v, u)) return v;
		for (int i = lg - 1; i >= 0; i--) {
			if (!is_ancestor(pa[i][v], u)) {
				v = pa[i][v];
			}
		}
		return pa[0][v];
	}
	int distance(int u, int v) {
		return dep[u] + dep[v] - 2 * dep[LCA(u, v)];
	}
	int induce(vector<int> subset, vector<int> &vertex_set, vector<int> &parent) {
		// input: a subset of vertices, which may contain duplicate vertices.
		// return: the root "r" of the compressed induced subtree T'
		// additional output: vertex_set = V(T'), parent[i] is the parent of vertex_set[i] in T' (using the labeling of T)
		// where parent[r] = r.
		
		// find LCAs
		vertex_set = subset;
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
		parent = vector<int>(vertex_set.size());
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

const int MAXN = 100005, SQRT = 1000;
int n, qn, tol[MAXN], pa[MAXN], qry[MAXN], ans[MAXN], is[MAXN];
vector<int> child[MAXN];

// subtree info
int cur, mark[MAXN], leave[MAXN], nxt[MAXN], id[MAXN];

// path info
vector<int> cnt[2*SQRT];
int add[2*SQRT];

int displeased(int v) {
	return (!is[v] && tol[v] - leave[v] <= 0);
}

void dfs1(int v) {
	leave[v] = is[v];
	for (int to : child[v]) {
		dfs1(to);
		leave[v] += leave[to];
	}
	cur += displeased(v);
}

void solve2(int l, vector<int> qs) {
	cur = 0;
	for (int i = 1; i <= n; i++) {
		mark[i] = 0;
		nxt[i] = id[i] = -1;
	}
	
	// subtree info
	for (int v : qs) {
		mark[v] = 1;
	}
	dfs1(1);
	
	vector<int> crit, parent;
	int root = T.induce(qs, crit, parent);
//	cout << "Induce:\n";
	for (int i = 0; i < crit.size(); i++) {
		nxt[crit[i]] = parent[i];
		id[crit[i]] = i;
//		cout << crit[i] << ' ' << parent[i] << endl;
	}
	nxt[root] = 0;
	
	// path
	for (int i = 0; i < crit.size(); i++) {
		int v = crit[i];
		add[i] = 0;
		cnt[i].resize(SQRT * 2 + 1, 0);
		fill(all_of(cnt[i]), 0);
		
		int u = pa[v];
		while (u != nxt[v]) {
			int val = tol[u] - leave[u];
			if (!is[u] && abs(val) <= SQRT) {
				cnt[i][val + SQRT]++;
			}
			u = pa[u];
		}
		for (int j = 1; j < cnt[i].size(); j++) {
			cnt[i][j] += cnt[i][j - 1];
		}
	}
	
	// query
	for (int i = 0; i < qs.size(); i++) {
		int v = qs[i];
		int chg = (is[v] ? -1 : 1);
		do {
			int sid = id[v];
			assert(sid != -1);
			cur += (cnt[sid][add[sid] + chg + SQRT] - cnt[sid][add[sid] + SQRT]);
			add[sid] += chg;
			
			cur -= displeased(v);
			if (v == qs[i])	{
				is[v] ^= 1;
			}
			leave[v] += chg;
			cur += displeased(v);
			v = nxt[v];
		} while (v != 0);
		ans[l + i] = cur;
	}
}

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
	cin >> n >> qn;
	pa[1] = 0; // pseudo
	for (int i = 2; i <= n; i++) {
		cin >> pa[i];
		child[pa[i]].push_back(i);
	}
	for (int i = 1; i <= n; i++) {
		cin >> tol[i];
		tol[i]++;
	}
	for (int i = 1; i <= qn; i++) {
		cin >> qry[i];
		qry[i] = abs(qry[i]);
	}
	
	T.init(n, child, 1);
	for (int i = 1; i <= qn; i += SQRT) {
		solve2(i, vector<int>(qry + i, qry + min(qn + 1, i + SQRT)));
	}
	for (int i = 1; i <= qn; i++) {
		cout << ans[i] << " \n"[i == qn];
	}
}


