void add(LL &x, LL y) {
	assert(0 <= x && x < MOD);
	assert(0 <= y && y < MOD);
	x += y;
	if (x >= MOD) x -= MOD;
}
void sub(LL &x, LL y) {
	assert(0 <= x && x < MOD);
	assert(0 <= y && y < MOD);
	x -= y;
	if (x < 0) x += MOD;
}
