
// extgcd & CRT
pair<LL, LL> ext_gcd( LL a, LL b) {
	if (b == 0) return make_pair(1, 0);
    if (a % b == 0) return make_pair(0, 1);
    pair<LL, LL> t = ext_gcd(b, a % b);
    return make_pair( t.second, t.first - a / b * t.second);
}
// Note that when ax + by = c, you should multiply c / gcd(a, b).
// LL g = __gcd(a, b), t1 = a / g, t2 = b / g; // in case you want to enumerate all
/* gcd based inv
LL mod_inv(LL x, LL mod) { // gcd(x,mod) must be 1
    return (exd_gcd(x,mod).first % mod + mod) % mod;
}
*/

// CRT, O(n lg C)
// no solution ==> (0, 0); input size = 0 ==> (0, 1)
// otherwise, solution x = y (mod z), z = LCM(m[i]) ==> return (y, z)
std::pair<long long, long long> crt(const std::vector<long long>& r,
                                    const std::vector<long long>& m) {
    assert(r.size() == m.size());
    int n = int(r.size());
    // Contracts: 0 <= r0 < m0
    long long r0 = 0, m0 = 1;
    for (int i = 0; i < n; i++) {
        assert(1 <= m[i]);
        long long r1 = (r[i] % m[i] + m[i]) % m[i], m1 = m[i];
        if (m0 < m1) {
            std::swap(r0, r1);
            std::swap(m0, m1);
        }
        if (m0 % m1 == 0) {
            if (r0 % m1 != r1) return {0, 0};
            continue;
        }
        // assume: m0 > m1, lcm(m0, m1) >= 2 * max(m0, m1)

        // (r0, m0), (r1, m1) -> (r2, m2 = lcm(m0, m1));
        // r2 % m0 = r0
        // r2 % m1 = r1
        // -> (r0 + x*m0) % m1 = r1
        // -> x*u0*g = r1-r0 (mod u1*g) (u0*g = m0, u1*g = m1)
        // -> x = (r1 - r0) / g * inv(u0) (mod u1)

        // im = inv(u0) (mod u1) (0 <= im < u1)
        long long g = __gcd(m0, m1), u0 = m0 / g, u1 = m1 / g, im;
        PLL temp = ext_gcd(u0, u1);
        im = (temp.first % u1 + u1) % u1;

        // |r1 - r0| < (m0 + m1) <= lcm(m0, m1)
        if ((r1 - r0) % g) return {0, 0};

        // u1 * u1 <= m1 * m1 / g / g <= m0 * m1 / g = lcm(m0, m1)
        long long x = (r1 - r0) / g % u1 * im % u1;

        // |r0| + |m0 * x|
        // < m0 + m0 * (u1 - 1)
        // = m0 + m0 * m1 / g - m0
        // = lcm(m0, m1)
        r0 += x * m0;
        m0 *= u1;  // -> lcm(m0, m1)
        if (r0 < 0) r0 += m0;
    }
    return {r0, m0};
}
