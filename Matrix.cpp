struct Matrix {
	int n;
	static const int SIZE = 2;
	vector<vector<LL>> v;
	
	// Handle empty matrix by yourself, many place will RE.
	// This is a very slow template
	Matrix(){ assert(0); /* GIVE SIZE!!*/ }
	Matrix(int _n, int _m) {
		v = vector<vector<LL>>(_n, vector<LL>(_m, 0));
	}
	Matrix(const Matrix &m) {
		v = m.v;
	}
	int size() {
		return v.size();
	}
	vector<LL>& operator [] (int idx) {
		return v[idx];
	}
	static Matrix unit(int n) {
		Matrix res(n, n);
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				res.v[i][j] = (i == j); // 0 here, for (+, min), others INF
			}
		}
		return res;
	}
	Matrix operator + (Matrix &mat) {
		int n = v.size(), m = v[0].size();
		Matrix res(n, m);
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				res[i][j] = (v[i][j] + mat[i][j]) % MOD;
			}
		}
		return res;
	}
	Matrix operator * (Matrix &mat) {
		int n = v.size(), p = v[0].size(), m = mat[0].size();
		assert(mat.size() == p);
		Matrix res(n, m);
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				for (int k = 0; k < p; k++) {
					res[i][j] = (res[i][j] + v[i][k] * mat[k][j]) % MOD;
				}
			}
		}
		return res;
	}
	Matrix power(LL pw) {
		Matrix res = unit(v.size()), m = *this;
		while (pw) {
			if (pw & 1) res = res * m;
			m = m * m;
			pw >>= 1;
		}
		return res;
	}
};
