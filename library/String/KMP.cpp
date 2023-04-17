vector<int> get_lps(const string &s) {
	// longest prefix suffix, 0-based
	vector<int> lps(s.size());	
	for (int i = 1; i < s.size(); i++) {
		int len = lps[i - 1];
		while (len > 0 && s[len] != s[i]) len = lps[len - 1];
		lps[i] = s[len] == s[i] ? len + 1 : 0;
	}
	return lps;
}

vector<int> match(const string &text, const string &pat) {
	// Find all matches
	int i = 0, j = 0;
	vector<int> occ, lps = get_lps(pat);
	while (i < text.size()) {
		if (text[i] == pat[j]) {
			i++;
			j++;
			if (j == pat.size()) {
				// Pattern found at text[i-j...i)
				occ.push_back(i - j);
				j = lps[j - 1];
			}
		}
		else if (j == 0) i++;
		else j = lps[j - 1];
	}
	return occ;
}
