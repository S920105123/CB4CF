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
//const int MAXN = 300005;
//const LL INF = (LL) 1e9 + 8763;
//const LL MOD = (LL) 998244353;
using namespace std;
template <class T> using min_heap = priority_queue<T, vector<T>, greater<T>>;
template <class T> using max_heap = priority_queue<T, vector<T>, less<T>>;
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
// function<vector<int>(int, int, int)> func = [&] (int m, int l, int c) {};

struct Partition_tree {
	// 0-based static partition tree with fractional cascading
	// Query are specified by CLOSED intervals
	// in O(lg n): rank query, select query, "given (ql, qr, x), find sum of elements in [ql, qr] which <= x"
	
	// Implementation:
	// Transform n to some 2^k
	// Each node of the tree is an OPEN interval [x, y) and stores the subsequence whose ranks are in [x, y)
	// The subsequence is represented by the indices and stored in ord[idx] (where idx is like segment tree indexing).
	// in O(nlgn), build: pcount[idx][i]: in prefix [0, i) of ord[idx], the number of elements in ord[idx] which is mapped to the left
	//                    psum[idx][i]: in prefix [0, i) of ord[idx], the sum of elements in ord[idx] which is mapped to the left
	
	
	int n;
	vector<int> A; // array
	
private:
	vector<int> sorted, sindex; // sorted sequence and the corresponding indices of the sorted sequence
	vector<vector<int>> ord, pcount;
	vector<vector<long long>> psum;
	void dfs_init(int x, int y, int idx) {
		ord[idx].assign(y - x + 1, n); // y - x elements plus a sentinel
		pcount[idx].assign(y - x + 1, 0);
		psum[idx].assign(y - x + 1, 0);
		if (y - x == 1) {
			ord[idx][0] = sindex[x];
			return;
		}
		int mid = (x + y) / 2;
		dfs_init(x, mid, idx * 2);
		dfs_init(mid, y, idx * 2 + 1);
		// merge
		int p1 = 0, p2 = 0, lson = idx * 2, rson = idx * 2 + 1;
		for (int i = 0; i < y - x; i++) {
			assert(p1 < ord[lson].size() && p2 < ord[rson].size());
			int t = -1, from = -1;
			if (ord[lson][p1] < ord[rson][p2]) {
				from = lson;
				t = p1++;
			}
			else {
				from = rson;
				t = p2++;
			}
			ord[idx][i] = ord[from][t];
			pcount[idx][i + 1] = pcount[idx][i] + (from == lson);
			psum[idx][i + 1] = psum[idx][i] + (from == lson ? A[ord[idx][i]] : 0);
		}
	}
	
public:
	void init(const vector<int> _A) {
		A = _A;
		n = 1;
		while (n < A.size()) {
			n *= 2;
		}
		A.resize(n, 2147483647); // Initial values do not matter, but large values make debug easier.
		sindex.resize(n);
		sorted = A;
		for (int i = 0; i < n; i++) {
			sindex[i] = i;
		}
		sort(sindex.begin(), sindex.end(), [&] (int a, int b) {
			return A[a] < A[b] || (A[a] == A[b] && a < b);
		});
		for (int i = 0; i < n; i++) {
			sorted[i] = A[sindex[i]];
		}
		
		ord.assign(2 * n, vector<int>());
		pcount.assign(2 * n, vector<int>());
		psum.assign(2 * n, vector<long long>());
		dfs_init(0, n, 1);
	}
	int get_rank(int ql, int qr, int val) {
		// get_rank(ql, qr, x): find # elements <= val in [ql, qr]
		qr++; // now, [ql, qr) is the query segment, and [x, y) is the rank interval
		int x = 0, y = n, idx = 1, res = 0;
		while (y - x > 1) {
			int mid = (x + y) / 2;
			if (sorted[mid] <= val) { // to right
				res += pcount[idx][qr] - pcount[idx][ql];
				ql = ql - pcount[idx][ql];
				qr = qr - pcount[idx][qr];
				idx = idx * 2 + 1;
				x = mid;
			}
			else { // to left
				ql = pcount[idx][ql];
				qr = pcount[idx][qr];
				idx = idx * 2;
				y = mid;
			}
		}
		return res + (ql != qr && sorted[x] <= val);
	}
	long long get_sum(int ql, int qr, int val) {
		// get_sum(ql, qr, x): find the sum elements <= val in [ql, qr]
		qr++;
		int x = 0, y = n, idx = 1;
		long long res = 0;
		while (y - x > 1) {
			int mid = (x + y) / 2;
			if (sorted[mid] <= val) {
				res += psum[idx][qr] - psum[idx][ql];
				ql = ql - pcount[idx][ql];
				qr = qr - pcount[idx][qr];
				idx = idx * 2 + 1;
				x = mid;
			}
			else { // to left
				ql = pcount[idx][ql];
				qr = pcount[idx][qr];
				idx = idx * 2;
				y = mid;
			}
		}
		return res + sorted[x] * (ql != qr && sorted[x] <= val);
	}
	int select(int ql, int qr, int k) {
		// select(int ql, int qr, int k): select the k-th element in [ql, qr], where 1 <= k <= qr - ql + 1
		qr++;
		assert(1 <= k && k <= qr - ql);
		int x = 0, y = n, idx = 1;
		while (y - x > 1) {
			int mid = (x + y) / 2, count = pcount[idx][qr] - pcount[idx][ql];
			if (count < k) {  // to right
				k -= count;
				ql = ql - pcount[idx][ql];
				qr = qr - pcount[idx][qr];
				idx = idx * 2 + 1;
				x = mid;
			}
			else { // to left
				ql = pcount[idx][ql];
				qr = pcount[idx][qr];
				idx = idx * 2;
				y = mid;
			}
		}
		assert(k == 1 && ql != qr);
		return sorted[x];
	}
} T;

struct Simulator {
	int n;
	vector<int> A; 
	void init(const vector<int> _A) {
		n = _A.size();
		A = _A;
	}
	int get_rank(int ql, int qr, int val) {
		int cnt = 0;
		for (int i = ql; i <= qr; i++) {
			cnt += (A[i] <= val);
		}
		return cnt;
	}
	long long get_sum(int ql, int qr, int val) {
		// get_rank(ql, qr, x): find the sum elements <= val in [ql, qr]
		long long cnt = 0;
		for (int i = ql; i <= qr; i++) {
			cnt += A[i] * (A[i] <= val);
		}
		return cnt;
	}
	int select(int ql, int qr, int k) {
		// select(int ql, int qr, int k): select the k-th element in [ql, qr]
		vector<int> sub(A.begin() + ql, A.begin() + qr + 1);
		sort(all_of(sub));
		return sub[k - 1];
	}
} S;

int main() {
	while (1) {
		const int MAXN = 1000000, MAXA = 1e9;
		int n = rng() % MAXN + 1, qn = rng() % MAXN + 1;
		vector<int> A(n);
//		cout << "Build: ";
		for (int i = 0; i < n; i++) {
			A[i] = rng() % MAXA;
//			cout << A[i] << " \n"[i == n - 1];
		}
		cout << n << ' ' << qn << endl;
		T.init(A);
		cout << "Here" << endl;
//		S.init(A);
		
		for (int q = 0; q < qn; q++) {
			int t = rng() % 3, ql = rng() % n, qr = rng() % n, val = rng() % MAXA;
			if (ql > qr) swap(ql, qr);
			long long ans1 = -1, ans2 = -2;
			if (t == 0) {
				ans1 = T.get_rank(ql, qr, val);
//				ans2 = S.get_rank(ql, qr, val);
			}
			else if (t == 1) {
				ans1 = T.get_sum(ql, qr, val);
//				ans2 = S.get_sum(ql, qr, val);
			}
			else {
				val = rng() % (qr - ql + 1) + 1;
				ans1 = T.select(ql, qr, val);
//				ans2 = S.select(ql, qr, val);
			}
//			cout << "Go " << t << " " << ql << " " << qr << " " << val << endl;
//			cout << "Get " << ans1 << " " << ans2 << endl;
//			assert(ans1 == ans2);
		}
		break;
	}
}
