const int BIT = 20;
struct Linear_basis {
	// sz: size of the basis, base[i]: basis vector with i-th bit = 1.
	// tot: how many numbers have been added? (rank = sz, nullity = tot - sz)
	// When basis contains only zero, its size is considered zero.
	LL tot, sz, base[BIT];
	void init() {
		sz = tot = 0;
		memset(base, 0, sizeof(base));
	}
	bool add(LL x) {
		// return 1 if x is added into basis
		tot++;
		for (int i = BIT - 1; i >= 0; i--) {
			if (x >> i & 1) {
				if (base[i] == 0) {
					base[i] = x;
					sz++;
					return 1;
				}
				else {
					x ^= base[i];
				}
			}
		}
		return 0;
	}
	bool is_ind(LL x) {
		// test if x is linearly independent to (all vectors in) this basis.
		for (int i = BIT - 1; i >= 0; i--) {
			if (x >> i & 1) {
				if (base[i] == 0) {
					return 1;
				}
				else {
					x ^= base[i];
				}
			}
		}
		return 0;
	}
} B;
