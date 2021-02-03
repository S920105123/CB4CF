void sos(vector<int>& a, bool inv) {
    const int n = a.size();

    for (int bit = 1; bit < n; bit <<= 1) {
        for (int i = 0; i < n; i++) {
            if (i & bit) {
                a[i] += (inv ? -1 : 1) * a[i ^ bit];
            }
        }
    }
}
