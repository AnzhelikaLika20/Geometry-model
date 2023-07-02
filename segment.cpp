#include "segment.h"

#include "line.h"
#include "point.h"
#include "vector.h"

geometry::Segment::Segment() {
    start_.SetX(0);
    start_.SetY(0);
    end_.SetX(0);
    end_.SetY(0);
}
double geometry::Segment::Distance(geometry::Point point) const {
    int64_t a = end_.GetY() - start_.GetY();
    int64_t b = start_.GetX() - end_.GetX();
    int64_t c = -a * start_.GetX() - b * start_.GetY();
    double mod = std::sqrt(static_cast<double>(a * a) + static_cast<double>(b * b));
    double distance = (static_cast<double>(a * point.GetX()) + static_cast<double>(b * point.GetY() + c)) / mod;
    return distance;
}
bool geometry::Segment::Degenerate() const {
    return start_.GetX() == end_.GetX() && start_.GetY() == end_.GetY();
}

geometry::Segment::Segment(geometry::Point start, geometry::Point end) {
    start_ = start;
    end_ = end;
}

geometry::Point geometry::Segment::GetStart() const {
    return start_;
}

geometry::Point geometry::Segment::GetEnd() const {
    return end_;
}
geometry::Segment& geometry::Segment::Move(const geometry::Vector& vector) {
    start_.SetX(start_.GetX() + vector.GetX());
    start_.SetY(start_.GetY() + vector.GetY());
    end_.SetX(end_.GetX() + vector.GetX());
    end_.SetY(end_.GetY() + vector.GetY());
    return *this;
}

bool geometry::Segment::ContainsPoint(const geometry::Point& point) const {
    if (GetStart() == GetEnd()) {
        return point == GetStart();
    }
    geometry::Vector vector1 = point - GetStart();
    geometry::Vector vector2 = GetEnd() - GetStart();
    return VectorMult(vector1, vector2) == 0 && point.GetX() >= std::min(GetStart().GetX(), GetEnd().GetX()) &&
           point.GetX() <= std::max(GetStart().GetX(), GetEnd().GetX()) &&
           point.GetY() >= std::min(GetStart().GetY(), GetEnd().GetY()) &&
           point.GetY() <= std::max(GetStart().GetY(), GetEnd().GetY());
}

bool geometry::Segment::CrossesSegment(const geometry::Segment& segment) const {
    Point a = segment.GetStart() < segment.GetEnd() ? segment.GetStart() : segment.GetEnd();
    Point b = segment.GetStart() < segment.GetEnd() ? segment.GetEnd() : segment.GetStart();
    Point c = GetStart() < GetEnd() ? GetStart() : GetEnd();
    Point d = GetStart() < GetEnd() ? GetEnd() : GetStart();
    int64_t vector_mult1 = VectorMult(a - b, a - c);
    int64_t vector_mult2 = VectorMult(a - b, a - d);
    int64_t vector_mult3 = VectorMult(c - d, c - a);
    int64_t vector_mult4 = VectorMult(c - d, c - b);
    if (segment.Degenerate() && Degenerate()) {
        return segment.start_ == this->GetStart();
    } else if (segment.Degenerate()) {
        return this->ContainsPoint(segment.GetStart());
    } else if (this->Degenerate()) {
        return segment.ContainsPoint(this->GetStart());
    }
    if ((vector_mult1 == 0 && vector_mult2 == 0) || (vector_mult3 == 0 && vector_mult4 == 0)) {
        if (a.GetX() != c.GetX()) {
            return (c.GetX() >= a.GetX() && c.GetX() <= b.GetX()) || (a.GetX() >= c.GetX() && a.GetX() <= d.GetX());
        } else {
            return (c.GetY() >= a.GetY() && c.GetY() <= b.GetY()) || (a.GetY() >= c.GetY() && a.GetY() <= d.GetY());
        }
    }
    return (vector_mult1 * vector_mult2 <= 0 && vector_mult3 * vector_mult4 <= 0);
};

geometry::Segment* geometry::Segment::Clone() const {
    geometry::Segment* new_line = new geometry::Segment(start_, end_);
    return new_line;
};
