struct Point {
	LL x, y; // When you want to add id, modify COPY constructor!!
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
	double angle(Point p) const {
		return atan2(cross(p), dot(p));
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

struct Line {
	// IMPORTANT, remember to transform between two-point form
	// and normal form by yourself, some methods may need them.
	Point p1,p2;
	double a,b,c; // ax+by+c=0
	Line(){} 
	Line(Point _p1, Point _p2) { p1 = _p1, p2 = _p2; }
    void pton() {
        a=p1.y-p2.y;
		b=p2.x-p1.x;
		c=-a*p1.x-b*p1.y;
    }
	double ori(const Point &p) {
		// For directed line, 0 if point on line
		// >0 if left, <0 if right
		return (p2-p1).cross(p-p1);
	}
	Point normal() { // normal vector to the left.
		Point dir=p2-p1;
		return {-dir.y,dir.x};
	}
	bool on_segment(const Point &p) {
		// Point on segment
		return relation(p)==0&&(p2-p).dot(p1-p)<=0;
	}
	bool parallel(const Line &l) {
		// Two line parallel
		return (p2-p1).cross(l.p2-l.p1)==0;
	}
	bool equal(const Line &l) {
		// Two line equal
		return relation(l.p1)==0&&relation(l.p2)==0;
	}
	bool cross_seg(const Line &seg) {
		// Line intersect segment
		Point dir=p2-p1;
		return dir.cross(seg.p1-p1)*dir.cross(seg.p2-p1)<=0;
	}
	int seg_intersect(const Line &s) const{
		// Two segment intersect
		// 0 -> no, 1 -> one point, -1 -> infinity
		Point dir=p2-p1, dir2=s.p2-s.p1;
		double c1=dir.cross(s.p2-p1);
		double c2=dir.cross(s.p1-p1);
		double c3=dir2.cross(p2-s.p1);
		double c4=dir2.cross(p1-s.p1);
		if (c1==0&&c2==0) {
			if((s.p2-p1).dot(s.p1-p1)>0&&(s.p2-p2).dot(s.p1-p2)>0&&
			   (p1-s.p1).dot(p2-s.p1)>0&&(p1-s.p2).dot(p2-s.p2)>0)return 0;
			if(p1==s.p1&&(p2-p1).dot(s.p2-p1)<=0)return 1;
			if(p1==s.p2&&(p2-p1).dot(s.p1-p1)<=0)return 1;
			if(p2==s.p1&&(p1-p2).dot(s.p2-p2)<=0)return 1;
			if(p2==s.p2&&(p1-p2).dot(s.p1-p2)<=0)return 1;
			return -1;
		}else if(c1*c2<=0&&c3*c4<=0)return 1; // Be aware overflow 
		return 0;
	}
	Point intersection(Line l) {
		// RE if d1.cross(d2) == 0 (parallel / coincide)
		Point d1 = p2 - p1, d2 = l.p2 - l.p1;
		return p1 + d1 * ((l.p1 - p1).cross(d2) / d1.cross(d2));
	}
	Point intersection2(Line l) {
		// By a, b, c
		// pton(); l.pton();
		// RE or {inf, inf} if they are parallel
		double a1 = a, b1 = b, c1 = c;
		double a2 = l.a, b2 = l.b, c2 = l.c;
		double deno = a1 * b2 - a2 * b1;
		return {(b1 * c2 - b2 * c1) / deno , (c1 * a2 - c2 * a1) / deno};
	}
	Point seg_intersection(Line &s) const {
		Point dir=p2-p1, dir2=s.p2-s.p1;
		// pton(); l.pton();
		double c1=dir.cross(s.p2-p1);
		double c2=dir.cross(s.p1-p1);
		double c3=dir2.cross(p2-s.p1);
		double c4=dir2.cross(p1-s.p1);
		if (c1==0&&c2==0) {
			if(p1==s.p1&&(p2-p1).dot(s.p2-p1)<=0)return p1;
			if(p1==s.p2&&(p2-p1).dot(s.p1-p1)<=0)return p1;
			if(p2==s.p1&&(p1-p2).dot(s.p2-p2)<=0)return p2;
			if(p2==s.p2&&(p1-p2).dot(s.p1-p2)<=0)return p2;
		}else if(c1*c2<=0&&c3*c4<=0)return line_intersection(s);
		// Reaches here means either INF or NOT ANY
		// Use seg_intersect to check OuO
        return {1234,4321};
	}
	double dist(const Point &p, bool is_segment) const {
		// Point to Line/segment
		Point dir=p2-p1,v=p-p1;
		if (is_segment) {
			if (dir.dot(v)<0) return v.len();
			if ((p1-p2).dot(p-p2)<0) return (p-p2).len();
		}
		double d=abs(dir.cross(v))/dir.len();
		return d;
	}
};
