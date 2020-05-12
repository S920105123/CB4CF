/* Common tangent, circle is a point c and radius r */
void get_tangent(Point c, double r1, double r2, vector<Line> &ans) {
    double r = r2 - r1;
    double z = c.x*c.x + c.y*c.y;
    double d = z - r*r;
    if (d < -EPS) return;
    d = sqrt(abs(d));
    Line l;
    l.a = (c.x * r + c.y * d) / z;
    l.b = (c.y * r - c.x * d) / z;
    l.c = r1;
    ans.push_back(l);
}
vector<Line> tangents(Circle a, Circle b) {
	// Tangent line of two circles, may have 0, 1, 2, 3, 4, inf solutions
	// In case 0 or inf (a = b), no line will be reported. Otherwise,
	// this program always find 4 lines, even if some of them are the same.
    vector<Line> ans;
    for (int i=-1; i<=1; i+=2)
        for (int j=-1; j<=1; j+=2)
            get_tangent(b.c-a.c, a.r*i, b.r*j, ans);
    for (size_t i=0; i<ans.size(); ++i)
        ans[i].c -= ans[i].a * a.c.x + ans[i].b * a.c.y;
    return ans;
}
// Circle-line intersection, line:ax+by+c=0
vector<Point> CL_intersection(Circle cir, Line li) {
	// li.pton(); // To Ax+By+C=0
	Point o = cir.c;
	li.c += li.a*o.x + li.b*o.y; // Shift w.r.t. cir.c
	
	vector<Point> res;
	double r = cir.r, a = li.a, b = li.b, c = li.c;
	double x0 = -a*c/(a*a+b*b), y0 = -b*c/(a*a+b*b);
	if (c*c > r*r*(a*a+b*b)+EPS) {
		return res; // No point
	}
	else if (abs(c*c - r*r*(a*a+b*b)) < EPS) {
		res.push_back({x0 + o.x, y0 + o.y}); // 1 point
	}
	else {
	    double d = r*r - c*c/(a*a+b*b);
	    double mult = sqrt (d / (a*a+b*b));
	    double ax, ay, bx, by;
	    ax = x0 + b * mult;
	    bx = x0 - b * mult;
	    ay = y0 - a * mult;
	    by = y0 + a * mult;
	    res.push_back({ax + o.x, ay + o.y}); // 2 points
	    res.push_back({bx + o.x, by + o.y});
	}
	return res;
}

// Circle-circle intersection
vector<Point> CC_intersection(Circle a, Circle b) {
	if (a.c.x == b.c.x && a.c.y == b.c.y && a.r == b.r) {
		return vector<Point>(); // coincide, inf points
	}
	Point o = a.c;
	b.c = b.c - o; // Shift
	a.c = {0.0, 0.0};
	
	double x2 = b.c.x, y2 = b.c.y, r1 = a.r, r2 = b.r;
	Line li = {-2*x2, -2*y2, x2*x2 + y2*y2 + r1*r1 - r2*r2}; // Ax+By+C = 0
	vector<Point> res = CL_intersection(a, li);
	for (Point &p : res) {
		p.x += o.x;
		p.y += o.y;
	}
	
	return res;
}
