#include "point.h"

#include "segment.h"

int64_t geometry::Point::GetX() const {
    return x_coord_;
}

int64_t geometry::Point::GetY() const {
    return y_coord_;
}

void geometry::Point::SetX(int64_t x) {
    x_coord_ = x;
}

void geometry::Point::SetY(int64_t y) {
    y_coord_ = y;
}

geometry::Point &geometry::Point::Move(const geometry::Vector &vector) {
    x_coord_ += vector.GetX();
    y_coord_ += vector.GetY();
    return *this;
}

bool geometry::Point::ContainsPoint(const geometry::Point &point) const {
    return x_coord_ == point.x_coord_ && y_coord_ == point.y_coord_;
}

bool geometry::Point::CrossesSegment(const geometry::Segment &segment) const {
    if (segment.GetStart() == segment.GetEnd()) {
        return *this == segment.GetStart();
    }
    Vector vector1 = *this - segment.GetStart();
    Vector vector2 = segment.GetEnd() - segment.GetStart();
    return VectorMult(vector1, vector2) == 0 &&
           GetX() >= std::min(segment.GetStart().GetX(), segment.GetEnd().GetX()) &&
           GetX() <= std::max(segment.GetStart().GetX(), segment.GetEnd().GetX()) &&
           GetY() >= std::min(segment.GetStart().GetY(), segment.GetEnd().GetY()) &&
           GetY() <= std::max(segment.GetStart().GetY(), segment.GetEnd().GetY());
}

geometry::Point *geometry::Point::Clone() const {
    Point *new_point = new Point(x_coord_, y_coord_);
    return new_point;
}

geometry::Point::Point(int64_t x, int64_t y) {
    x_coord_ = x;
    y_coord_ = y;
}

geometry::Vector geometry::Point::operator-(geometry::Point other) const {
    return geometry::Vector(x_coord_ - other.GetX(), y_coord_ - other.GetY());
}

bool geometry::Point::operator==(const geometry::Point &point) const {
    if (GetX() == point.GetX() && GetY() == point.GetY()) {
        return true;
    }
    return false;
}

bool geometry::Point::operator<(const geometry::Point &point) const {
    if (GetX() < point.GetX()) {
        return true;
    }
    return GetY() < point.GetY();
}

bool geometry::Point::operator>=(const geometry::Point &point) const {
    return !(*this < point);
}
