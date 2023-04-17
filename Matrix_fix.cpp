struct Matrix {
	static const int SIZE = 3;
	LL v[SIZE][SIZE];
	
	Matrix() { // default, zero matrix
		for (int i = 0; i < SIZE; i++) {
			for (int j = 0; j < SIZE; j++) {
				v[i][j] = 0;
//				v[i][j] = INF; // for (min, +)
			}
		}
	}
	Matrix(const Matrix &m) { // copy constructor
		for (int i = 0; i < SIZE; i++) {
			for (int j = 0; j < SIZE; j++) {
				v[i][j] = m.v[i][j];
			}
		}
	}
	static Matrix identity() {
		Matrix m;
		for (int i = 0; i < SIZE; i++) {
			for (int j = 0; j < SIZE; j++) {
				m.v[i][j] = (i == j ? 1 : 0);
//				m.v[i][j] = (i == j ? 0 : INF); // for (min, +)
			}
		}
		return m;
	}
	inline LL* operator [] (int idx) { // allowing access to mat[i][j]
		return v[idx];
	}
	inline LL at(int i, int j) const {
		return v[i][j];
	}
	
	bool operator == (const Matrix &mat) const {
		for (int i = 0; i < SIZE; i++) {
			for (int j = 0; j < SIZE; j++) {
				if (v[i][j] != mat.at(i, j)) {
					return 0;
				}
			}
		}
		return 1;
	}
	Matrix operator * (const Matrix &mat) const {
		Matrix res;
		for (int i = 0; i < SIZE; i++) {
			for (int j = 0; j < SIZE; j++) {
				for (int k = 0; k < SIZE; k++) {
					res[i][j] = (res[i][j] + v[i][k] * mat.at(k, j)) % MOD;
//					res[i][j] = min(res[i][j], v[i][k] + mat.at(k, j)); // for (min, +)
				}
			}
		}
		return res;
	}
	Matrix operator + (const Matrix &mat) const {
		Matrix res;
		for (int i = 0; i < SIZE; i++) {
			for (int j = 0; j < SIZE; j++) {
				res[i][j] = (v[i][j] + mat.at(i, j)) % MOD;
//				res[i][j] = min(v[i][j], mat.at(i, j)); // for (min, +)
			}
		}
		return res;
	}
	Matrix power(LL pw) const {
		Matrix res, m = *this;
		while (pw) {
			if (pw & 1) res = res * m;
			m = m * m;
			pw >>= 1;
		}
		return res;
	}
	friend ostream& operator << (ostream &os, const Matrix &mat);
};

ostream& operator << (ostream &os, const Matrix &mat) {
	os << "\nPrint matrix:\n";
	for (int i = 0; i < Matrix::SIZE; i++) {
		for (int j = 0; j < Matrix::SIZE; j++) {
			os << mat.at(i, j) << " \n"[j + 1 == Matrix::SIZE];
		}
	}
	os << '\n';
}

