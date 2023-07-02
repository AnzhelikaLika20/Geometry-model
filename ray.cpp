#include "i_shape.h"
#include "point.h"
#include "segment.h"
#include "vector.h"

namespace geometry {
class Ray : public IShape {
private:
    Point start_;
    Point end_;

public:
    Ray();

    Ray(Point first, Point second);

    Ray& Move(const Vector& vector) override;

    bool ContainsPoint(const Point& point) const override;

    bool CrossesSegment(const Segment& segment) const override;

    Ray* Clone() const override;

    Point GetStart() const;

    Point GetEnd() const;
};
}  // namespace geometry

geometry::Ray::Ray() {
    start_ = Point(0, 0);
    end_ = Point(0, 0);
}

geometry::Ray::Ray(geometry::Point first, geometry::Point second) {
    start_ = first;
    end_ = second;
}

geometry::Ray& geometry::Ray::Move(const geometry::Vector& vector) {
    start_.SetX(start_.GetX() + vector.GetX());
    start_.SetY(start_.GetY() + vector.GetY());
    end_.SetX(end_.GetX() + vector.GetX());
    end_.SetY(end_.GetY() + vector.GetY());
    return *this;
}

bool geometry::Ray::ContainsPoint(const geometry::Point& point) const {
    if (start_ == end_) {
        return start_ == point;
    }
    geometry::Vector vector1 = point - GetStart();
    geometry::Vector vector2 = GetEnd() - GetStart();
    return ScalarMult(vector1, vector2) >= 0 && VectorMult(vector1, vector2) == 0;
}

bool geometry::Ray::CrossesSegment(const geometry::Segment& segment) const {
    Point a = segment.GetStart();
    Point b = segment.GetEnd();
    Point c = GetStart();
    Point d = GetEnd();
    geometry::Vector direction = d - c;
    geometry::Vector vect1 = c - a;
    geometry::Vector vect2 = b - a;
    geometry::Vector vect3 = Vector(-direction.GetY(), direction.GetX());
    if (ScalarMult(vect2, vect3) == 0) {
        return ContainsPoint(segment.GetStart()) || ContainsPoint(segment.GetEnd());
    }
    double k1 = static_cast<double>(VectorMult(vect2, vect1)) / static_cast<double>(ScalarMult(vect2, vect3));
    double k2 = static_cast<double>(ScalarMult(vect1, vect3)) / static_cast<double>(ScalarMult(vect2, vect3));
    return k1 >= 0.0 && k2 >= 0.0 && k2 <= 1.0;
}

geometry::Ray* geometry::Ray::Clone() const {
    geometry::Ray* new_ray = new geometry::Ray(start_, end_);
    return new_ray;
}

geometry::Point geometry::Ray::GetStart() const {
    return start_;
}

geometry::Point geometry::Ray::GetEnd() const {
    return end_;
}
