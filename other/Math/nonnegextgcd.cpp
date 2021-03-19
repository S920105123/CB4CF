// extgcd
pair<LL, LL> ext_gcd( LL a, LL b) {
	if (b == 0) return make_pair(1, 0);
    if (a % b == 0) return make_pair(0, 1);
    pair<LL, LL> t = ext_gcd(b, a % b);
    return make_pair( t.second, t.first - a / b * t.second);
}

// ax + by = c. Assume a >= 0 and b >= 0.
// Among all solutions, pick the one with smallest NON-NEGATIVE x
// return (-1, -1) if no solution
pair<LL, LL> nonneg_ext_gcd(LL a, LL b, LL c) {
	assert(a >= 0 && b >= 0);
	PLL p = ext_gcd(a, b);
	LL g = a * p.first + b * p.second;
	LL t0 = b / g, t1 = a / g; // note that (x-t0, y+t1) is the next solution
	if (c % g != 0) {
		return make_pair(-1LL, -1LL);
	}
	
	p.first *= c / g;
	p.second *= c / g;
	if (p.first < 0) {
		LL mul = -p.first / t0;
		p.first += t0 * mul;
		p.second -= t1 * mul;
	}
	p.first += t0;
	p.second -= t1;
	
	// now p.first is non-negative
	LL mul = p.first / t0;
	p.first -= t0 * mul;
	p.second += t1 * mul;
    return p;
}
