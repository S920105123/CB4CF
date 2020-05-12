vector<int> lps; // longest prefix suffix, 0-based
vector<int> match(const string &text, const string &pat) {
	/* Find all match */
	lps.resize(pat.size());	
	/* DP */
	lps[0]=0;
	for (int i=1; i<pat.size(); i++) {
		int len=lps[i - 1];
		while(len>0 && pat[len]!=pat[i]) len=lps[len - 1];
		lps[i] = pat[len]==pat[i] ? len+1 : 0;
	}	
	/* Match */
	int i = 0, j = 0;
	vector<int> occ;
	while (i < text.size()) {
		if (text[i] == pat[j]) {
			i++;
			j++;
			if (j == pat.size()) {
				// Find one pattern at text[i-j...i)
				occ.push_back(i - j);
				j = lps[j - 1];
			}
		}
		else if (j == 0) i++;
		else j = lps[j - 1];
	}
	return occ;
}
