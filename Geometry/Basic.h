/* --start geometry library --*/
const double EPS = 1e-10;
#define equals(a, b) (fabs((a) -(b)) < EPS)

class Point {
private:

public:

    double x, y;

    Point(double x = 0, double y = 0) : x(x), y(y) {}

    Point operator+(Point &p) {
        return Point(x + p.x, y + p.y);
    }

    Point operator-(Point &p) {
        return Point(x - p.x, y - p.y);
    }

    /**
     * スカラー倍する
     * @param k
     * @return
     */
    Point operator*(double k) {
        return Point(x * k, y * k);
    }

    /* 大きさの2乗を表す */
    double norm() {
        return x * x + y * y;
    }

    /**
     * 大きさを返す
     * @return
     */
    double abs() {
        return sqrt(norm());
    }

    /**
     * 同じかどうか
     */
    bool operator==(const Point &p) const {
        return fabs(x - p.x) < EPS && fabs(y - p.y) < EPS;
    }


};

//ベクトル
typedef Point Vector;

//線分
struct Segment {
    Point p1, p2;
};

//直線
typedef Segment Line;

//円
class Circle {
public:
    Point c;
    double r;

    Circle(Point c = Point(), double r = 0.0) : c(c), r(r) {}
};


//内積
double dot(Vector a, Vector b) {
    return a.x * b.x + a.y * b.y;
}

//外積
double cross(Vector a, Vector b) {
    return a.x * b.y - a.y * b.x;
}

typedef vector <Point> Polygon;

//ベクトルの直行判定
bool isOrthogonal(Vector a, Vector b) {
    return equals(dot(a, b), 0.0);
}

bool isOrthogonal(Point a1, Point a2, Point b1, Point b2) {
    return isOrthogonal(a1 - a2, b1 - b2);
}

bool isOrthogonal(Segment s1, Segment s2) {
    return equals(dot(s1.p2 - s1.p1, s2.p2 - s2.p1), 0.0);
}

//ベクトルの平行判定
bool isParallel(Vector a, Vector b) {
    return equals(cross(a, b), 0.0);
}

bool isParallel(Point a1, Point a2, Point b1, Point b2) {
    return isParallel(a1 - a2, b1 - b2);
}

bool isParallel(Segment s1, Segment s2) {
    return equals(cross(s1.p2 - s1.p1, s2.p2 - s2.p2), 0.0);
}

//射影
//線分sに対するpの射影
Point project(Segment s, Point p) {
    Vector base = s.p2 - s.p1;
    double r = dot(p - s.p1, base) / base.norm();
    return s.p1 + base * r;
}

//反射
Point reflect(Segment s, Point p) {
    return p + (project(s, p) - p) * 2.0;
}

//反時計回り
static const int COUNTER_CLOCKWISE = -1;    //p0,p1,p2が反時計回り
static const int CLOCKWISE = -1;            //p0,p1,p2が時計回り
static const int ONLINE_BACK = 2;           //p2,p0,p1が同一直線状
static const int ONLINE_FRONT = -2;         //p0,p1,p2が同一直線状
static const int ON_SEGMENT = 0;            //p2がp0p1上にある

int ccw(Point p0, Point p1, Point p2) {
    Vector a = p1 - p0;
    Vector b = p2 - p0;

    if (cross(a, b) > EPS) return COUNTER_CLOCKWISE;
    if (cross(a, b) < EPS) return CLOCKWISE;
    if (dot(a, b) < -EPS) return ONLINE_BACK;
    if (a.norm() < b.norm()) return ONLINE_FRONT;

    return ON_SEGMENT;
}

//線分の交差判定
bool intersect(Point p1, Point p2, Point p3, Point p4) {
    return (ccw(p1, p2, p3) * ccw(p1, p2, p4) <= 0 && ccw(p3, p4, p1) * ccw(p3, p4, p2) <= 0);
}

bool intersect(Segment s1, Segment s2) {
    return intersect(s1.p1, s1.p2, s2.p1, s2.p2);
}

//2点間の距離
double getDistance(Point a, Point b) {
    return (a - b).abs();
}

//点と直線の距離
double getDistanceLP(Line l, Point p) {
    return abs(cross(l.p2 - l.p1, p - l.p1)) / (l.p2 - l.p1).abs();
}

//点と線分の距離
double getDistanceSP(Segment s, Point p) {
    if (dot(s.p2 - s.p1, p - s.p1) < 0.0) return (p - s.p1).abs();
    if (dot(s.p1 - s.p2, p - s.p2) < 0.0) return (p - s.p2).abs();
    return getDistanceLP(s, p);
}

//線分と線分の距離
double getDistance(Segment s1, Segment s2) {
    if (intersect(s1, s2)) return 0.0;
    return min(min(getDistanceSP(s1, s2.p1), getDistanceSP(s1, s2.p2)),
               min(getDistanceSP(s2, s1.p1), getDistanceSP(s2, s1.p2)));
}
