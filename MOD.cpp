auto add = [&](int& a, int b) -> void {
	a += b;
	a = (a >= MOD ? a - MOD : a);
};
auto sub = [&](int& a, int b) -> void {
	a -= b;
	a = (a < 0 ? a + MOD : a);
};

