#define LL long long 
struct Hash {
	// 0-based, xp[i]: BASE^i
	// hval[i]: sum of str[j] * xp[j - i]
	LL base, mod;
	vector<LL> xp, hval;
	
	void init(const string &str, LL _base, LL _mod) {
		int len = str.size();
		xp.resize(len + 1);
		hval.resize(len + 1);
		xp[0] = 1;
		for (int i = 1; i <= len; i++) {
			xp[i] = (xp[i - 1] * base) % mod;
		}
		hval[len] = 0;
		for (int i = len - 1; i >= 0; i--) {
			hval[i] = (hval[i + 1] * base + (LL) str[i]) % mod;
		}
	}
	
	LL get_hash(int l, int r) { // [0, len - 1]
		return ((hval[l] - hval[r + 1] * xp[r - l + 1]) % mod + mod) % mod;
	}
};
