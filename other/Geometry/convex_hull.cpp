struct Point {
	double x, y;
	double cross(const Point &p) const {
		return x * p.y - y * p.x;
	}
	Point operator - (const Point &p) const {
		return {x - p.x, y - p.y};
	}
};

vector<Point> convex_hull(vector<Point> ps) {
	// Find convex hull of ps, store in hull
	vector<Point> H(ps.size() + 1);
	sort(ps.begin(), ps.end(), [&] (const Point &a, const Point &b) {
		return a.x < b.x || (a.x == b.x && a.y < b.y);
	});
	int t = -1; // top
	for (int i = 0; i < ps.size(); i++) {
		// cross<-EPS -> count collinear, cross<EPS -> not
		while (t >= 1 && (H[t] - H[t - 1]).cross(ps[i] - H[t]) < EPS) {
			t--;
		}
		H[++t] = ps[i];
	}
	int low = t;
	for (int i = ps.size() - 2; i >= 0; i--) {
		// cross<-EPS -> count collinear, cross<EPS -> not
		while (t > low && (H[t] - H[t - 1]).cross(ps[i] - H[t]) < EPS) {
			t--;
		}
		H[++t] = ps[i];
	}
	H.resize(t); // pop_back is included
	return H;
}
