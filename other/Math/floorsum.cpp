LL floorsum(LL n, LL m, LL a, LL b) {
	// sigma i=0~n-1 floor((a*i+b) / m)
	// Note that if a, b can > m, this value can be as large as O(a*n*n).
	LL res = 0;
	if (a >= m) {
		res += a / m * n * (n - 1) / 2;
		a %= m;
	}
	if (b >= m) {
		res += b / m * n;
		b %= m;
	}
	
	LL ymax = (a * (n - 1) + b) / m;
	if (a == 0 || ymax == 0) {
		return res;
	}
	return res + n * ymax - floorsum(ymax, a, m, m + a - b - 1);
}
