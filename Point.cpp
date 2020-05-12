struct Point {
	LL x, y;
	Point() { x = y = 0; }
	Point(LL _x, LL _y) : x(_x), y(_y) {}
	Point(const Point &p) { x = p.x; y = p.y; }
	Point operator + (Point p) const {
		return Point(x + p.x, y + p.y);
	}
	Point operator - (Point p) const {
		return Point(x - p.x, y - p.y);
	}
	Point operator * (LL mul) const {
		return Point(x * mul, y * mul);
	}
	LL cross(Point p) const {
		return (LL) x * p.y - (LL) y * p.x;
	}
	LL dot(Point p) const {
		return (LL) x * p.x + (LL) y * p.y;
	}
	int quadrant() const {
		// return 1 or 2 or 3 or 4
		if (x > 0 && y >= 0) return 1;
		if (x <= 0 && y > 0) return 2;
		if (x < 0 && y <= 0) return 3;
		return 4;
	}
	static angle_cmp(Point a, Point b) {
		// Return (a < b)
		if (b.x == 0 && b.y == 0) return 0;
		if (a.x == 0 && a.y == 0) return 1;
		int q1 = a.quadrant(), q2 = b.quadrant();
		if (q1 != q2) return q1 < q2;
		LL crs = a.cross(b);
		if (crs != 0) return crs > 0;
		return abs(a.x) + abs(a.y) < abs(b.x) + abs(b.y);
	}
};
