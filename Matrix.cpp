struct Matrix {
	int n;
	static const int SIZE = 2;
	LL v[SIZE][SIZE];
	
	Matrix(){ assert(0); /* GIVE SIZE!!*/ }
	Matrix(int _n) {
		n = _n;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				v[i][j] = 0;
			}
		}
	}
	Matrix(const Matrix &m) {
		n = m.n;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				v[i][j] = m.v[i][j];
			}
		}
	}
	LL* operator [] (int idx) {
		return v[idx];
	}
	static Matrix unit(int n) {
		Matrix m(n);
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				m.v[i][j] = (i == j);
			}
		}
		return m;
	}
	Matrix operator + (Matrix m) {
		Matrix res(n);
		assert(n == m.n);
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				res[i][j] = (v[i][j] + m[i][j]) % MOD;
			}
		}
		return res;
	}
	Matrix operator * (Matrix m) {
		Matrix res(n);
		assert(n == m.n);
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				for (int k = 0; k < n; k++) {
					res[i][j] = (res[i][j] + v[i][k] * m[k][j]) % MOD;
				}
			}
		}
		return res;
	}
	Matrix power(LL pw) {
		Matrix res = unit(n), m = *this;
		while (pw) {
			if (pw & 1) res = res * m;
			m = m * m;
			pw >>= 1;
		}
		return res;
	}
};

