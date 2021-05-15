LL qpow(LL a, LL pw, LL mod) {
	LL res = 1;
	a %= mod;
	while (pw) {
		if (pw & 1) res = res * a % mod;
		a = a * a % mod;
		pw >>= 1;
	}
	return res;
}
LL mod_inv(LL a, LL mod) {
	// for prime
	return qpow(a, mod - 2, mod);
}

// Find solution of system of n linear equations, N^3.
// This template work under modulo PRIME (change mod_inv if needed) 
// The solution is stored in sol, return -1 if no sol.
// Otherwise, return the nullity of the system of equations, 0 ==> unique sol, x ==> MOD^x sol
int gauss(vector<vector<LL>> coe, vector<LL> &sol, LL mod) {
    // n equations having the form a1x1 + a2x2 + ... + anxn = c.
    // coe should be an n * (n + 1) matrix, each row is <a1, a2, ..., an, c>.
    
    int n = coe.size(), ptr = 0;
    for (int i = 0; i < n; i++) {
        int pos = ptr;
        for (int r = ptr; r < n; r++) {
            if (coe[r][i] != 0) {
                pos = r;
                break;
            }
        }
        if (coe[pos][i] == 0) continue; // target column all zeros
        
        swap(coe[pos], coe[ptr]);
        for (int r = ptr + 1; r < n; r++) {
            LL mul = coe[r][i] * mod_inv(coe[ptr][i], mod) % mod;
            for (int c = 0; c < n + 1; c++) {
                coe[r][c] = (coe[r][c] - coe[ptr][c] * mul) % mod;
            }
            assert(coe[r][i] == 0);
        }
        ptr++;
    }
    
    // reorder the rows, first non-zero = i ==> go to i-th row.
    int nul = n;
    for (int i = n - 1; i >= 0; i--) {
    	for (int j = 0; j < n; j++) {
    		if (coe[i][j] != 0) {
    			swap(coe[i], coe[j]);
    			nul--;
    			break;
			}
		}
	}

	// Solution recovery 
	sol = vector<LL>(n, 0);
    for (int i = n - 1; i >= 0; i--) {
        LL sum = coe[i][n] % mod;
        for (int j = i + 1; j < n; j++) {
            sum = (sum - coe[i][j] * sol[j]) % mod;
        }
        
        if (coe[i][i] == 0) {
        	if (sum != 0) {
        		return -1;
			}
        	sol[i] = 0; // or any number % MOD
		}
        sol[i] = (sum * mod_inv(coe[i][i], mod) % mod + mod) % mod;
    }
    return nul;
}



// *********** double gauss ************* //
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
