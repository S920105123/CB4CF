 
struct SA { 
    /* sa: sorted suffices, rank: rank of text[i] */
    /* lcp: lcp[i] = LCP(sa[i], sa[i-1]), lcp[0] = 0 */
    // Init is included in build
    // 0-indexed, NO NEED to add $
//    static const int MAXL = 1000005;
    string text;
    int sa[MAXL], rank[MAXL], lcp[MAXL], cnt[MAXL];
    void build(const string &_text/* or vetor<int>*/) {
        // presort, order by first character
        text = _text;
        int sz = text.size();
        vector<int> ord(text.begin(), text.end());
        sort(ord.begin(), ord.end());
        ord.erase(unique(ord.begin(), ord.end()), ord.end());
        for (int i = 0; i < sz; i++) {
            rank[i] = lower_bound(ord.begin(), ord.end(), text[i]) - ord.begin();
            sa[i] = i;
        }
        sort(sa, sa + sz, [&] (int a, int b) {
            return (rank[a] < rank[b]) || (rank[a] == rank[b] && a < b);
        });
 
        // counting sort, len ==> len * 2
    	int lim = ord.size(), *nsa = lcp, *nrank = lcp;
    	for (int len = 1; len < sz; len <<= 1) {
    		int num = 0;
    		for (int i = sz - len; i < sz; i++) nsa[num++] = i;
    		for (int i = 0; i < sz; i++) if (sa[i] >= len) nsa[num++] = sa[i] - len;
 
    		for (int i = 0; i < lim; i++) cnt[i] = 0;
    		for (int i = 0; i < sz; i++) cnt[ rank[i] ]++;
    		for (int i = 1; i < lim; i++) cnt[i] += cnt[i - 1];
    		for (int i = sz - 1; i >= 0; i--) sa[ --cnt[rank[nsa[i]]] ] = nsa[i];
 
    		num = 0;
    		nrank[sa[0]] = num++;
    		for (int i = 1; i < sz; i++) {
                int x = sa[i], y = sa[i - 1];
    			if (rank[x] == rank[y] && max(x, y) + len < sz && rank[x + len] == rank[y + len]) {
                    nrank[sa[i]] = num - 1;
                }
    			else {
                    nrank[sa[i]] = num++;
                }
    		}
 
    		lim = num;
    		copy(nrank, nrank + sz, rank);
            if (num >= sz) {
                break;
            }
    	}
 
    	/* LCP */
    	int len = 0;
    	lcp[0] = 0;
    	for (int i = 0; i < sz; i++) {
    		if (rank[i] == 0) continue;
    		len = max(0, len - 1);
    		int j = sa[rank[i] - 1];
    		while (max(i, j) + len < sz && text[i + len] == text[j + len]) len++;
    		lcp[rank[i]] = len;
    	}
    }
} S;
 
