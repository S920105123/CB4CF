// Solve system of linear equations on n variables, 0-based
// add equation: O(n * min(m, n)), construct solution: O(n * min(m, n)), m: #equations added
// This template work under modulo G_MOD (change mod_inv if G_MOD is not prime)
struct Incremental_gauss {
	static const LL G_MOD = 3;
	int vn, exist; // #variables, [is a solution exists]
	vector<vector<LL>> basis;
	LL mod_inv(LL a) {
		LL res = 1, pw = G_MOD - 2;
		while (pw) {
			if (pw & 1) res = res * a % G_MOD;
			a = a * a % G_MOD;
			pw >>= 1;
		}
		return res;
	}
	void init(int _vn) {
		vn = _vn;
		exist = 1;
		basis = vector<vector<LL>>(vn, vector<LL>(vn + 1));
	}
	void add_equation(vector<LL> eqn) {
		// a1x1 + a2x2 + ... anxn = a[n+1], ai in [0, mod)
		assert(eqn.size() == vn + 1);
		for (int i = 0; i < vn; i++) {
			if (eqn[i] != 0) {
				if (basis[i][i] == 0) {
					basis[i] = eqn;
					return;
				}
				else {
					LL mul = eqn[i] * mod_inv(basis[i][i]);
					for (int j = i; j <= vn; j++) {
						eqn[j] = (eqn[j] - mul * basis[i][j]) % G_MOD;
						if (eqn[j] < 0)  {
							eqn[j] += G_MOD;
						}
					}
				}
			}
		}
		if (eqn[vn] != 0) {
			exist = 0;
		}
	}
	int solve(vector<LL> &sol) {
		// return: inf solution ==> -1, no solution ==> 0, unique solution ==> 1
		if (!exist) {
			return 0;
		}
		int cnt = 0;
		sol = vector<LL>(vn, 0);
		for (int i = vn - 1; i >= 0; i--) {
			if (basis[i][i] != 0) {
				LL sum = basis[i][vn];
				for (int j = i + 1; j < vn; j++) {
					sum = (sum - basis[i][j] * sol[j]) % G_MOD;
				}
				if (sum < 0) {
					sum += G_MOD;
				}
				sol[i] = sum * mod_inv(basis[i][i]) % G_MOD;
				cnt++;
			}
		}
		return (cnt == vn ? 1 : -1);
	}
} algo;


// *********** double gauss from cp algo ************* //
// return: no sol ==> 0, one sol ==> 1, inf sol ==> 2
const double EPS = 1e-9;
const int INF_SOLUTION = 2;

int gauss (vector < vector<double> > a, vector<double> & ans) {
    int n = (int) a.size();
    int m = (int) a[0].size() - 1;

    vector<int> where (m, -1);
    for (int col=0, row=0; col<m && row<n; ++col) {
        int sel = row;
        for (int i=row; i<n; ++i)
            if (abs (a[i][col]) > abs (a[sel][col]))
                sel = i;
        if (abs (a[sel][col]) < EPS)
            continue;
        for (int i=col; i<=m; ++i)
            swap (a[sel][i], a[row][i]);
        where[col] = row;

        for (int i=0; i<n; ++i)
            if (i != row) {
                double c = a[i][col] / a[row][col];
                for (int j=col; j<=m; ++j)
                    a[i][j] -= a[row][j] * c;
            }
        ++row;
    }

    ans.assign (m, 0);
    for (int i=0; i<m; ++i)
        if (where[i] != -1)
            ans[i] = a[where[i]][m] / a[where[i]][i];
    for (int i=0; i<n; ++i) {
        double sum = 0;
        for (int j=0; j<m; ++j)
            sum += ans[j] * a[i][j];
        if (abs (sum - a[i][m]) > EPS)
            return 0;
    }

    for (int i=0; i<m; ++i)
        if (where[i] == -1)
            return INF_SOLUTION;
    return 1;
}
