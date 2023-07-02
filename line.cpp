#include "line.h"

#include "segment.h"

geometry::Line::Line() {
    start_ = Point(0, 0);
    end_ = Point(0, 0);
}

int64_t geometry::Line::GetA() const {
    return end_.GetY() - start_.GetY();
}

int64_t geometry::Line::GetB() const {
    return start_.GetX() - end_.GetX();
}

int64_t geometry::Line::GetC() const {
    return -GetA() * start_.GetX() - GetB() * start_.GetY();
}

geometry::Line::Line(geometry::Point start, geometry::Point end) {
    start_ = start;
    end_ = end;
}

double geometry::Line::Distance(geometry::Point point) const {
    double mod = std::sqrt(static_cast<double>(GetA() * GetA()) + static_cast<double>(GetB() * GetB()));
    double distance =
        (static_cast<double>(GetA() * point.GetX()) + static_cast<double>(GetB() * point.GetY() + GetC())) / mod;
    return distance;
}

geometry::Line& geometry::Line::Move(const geometry::Vector& vector) {
    start_.SetX(start_.GetX() + vector.GetX());
    start_.SetY(start_.GetY() + vector.GetY());
    end_.SetX(end_.GetX() + vector.GetX());
    end_.SetY(end_.GetY() + vector.GetY());
    return *this;
}

bool geometry::Line::ContainsPoint(const geometry::Point& point) const {
    Vector vector1 = point - start_;
    Vector vector2 = end_ - start_;
    return VectorMult(vector1, vector2) == 0;
}

bool geometry::Line::CrossesSegment(const geometry::Segment& segment) const {
    int64_t line_with_start = segment.GetStart().GetX() * GetA() + segment.GetStart().GetY() * GetB() + GetC();
    int64_t line_with_end = segment.GetEnd().GetX() * GetA() + segment.GetEnd().GetY() * GetB() + GetC();
    if (line_with_start * line_with_end <= 0) {
        return true;
    }
    return false;
}

geometry::Line* geometry::Line::Clone() const {
    Line* new_line = new Line(start_, end_);
    return new_line;
}
