/*
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
*/
// This template work under modulo MOD
vector<LL> gauss(vector<vector<LL>> &coe) {
    // Find solution of system of n linear equations, N^3.
    // n equations having the form a1x1 + a2x2 + ... + anxn = c.
    // coe should be an n * (n + 1) matrix, each row is <a1, a2, ..., an, c>.
    
    int n = coe.size();
    for (int i = 0; i < n - 1; i++) {
        int r = i;
        for (int j = i; j < n; j++) {
            if (coe[j][i] != 0) {
                r = j;
                break;
            }
        }
        if (coe[r][i] == 0) continue; // target column all zeros
        for (int j = 0; j < n + 1; j++) {
            swap(coe[i][j], coe[r][j]);
        }
        for (r = i + 1; r < n; r++) {
            LL mul = coe[r][i] * mod_inv(coe[i][i], MOD);
            for (int c = 0; c < n + 1; c++) {
                coe[r][c] = (coe[r][c] - coe[i][c] * mul) % MOD;
            }
        }
    }
 
    vector<LL> sol(n);
    for (int i = n - 1; i >= 0; i--) {
        LL val = coe[i][n];
        for (int j = i + 1; j < n; j++) {
            val = (val - coe[i][j] * sol[j]) % MOD;
        }
        if (coe[i][i] == 0) {
        	// no sol or inf sol.
        	// if val == 0, then inf solutions.
        	// otherwise, no solutions
			return vector<LL>();
		}
        sol[i] = (val * mod_inv(coe[i][i], MOD) % MOD + MOD) % MOD;
    }
    return sol;
}
