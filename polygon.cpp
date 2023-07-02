#include "polygon.h"

#include <vector>

#include "ray.cpp"

geometry::Polygon::Polygon() {
    num_points_ = 0;
    points_ = std::vector<Point>();
}

geometry::Polygon::Polygon(std::vector<Point> points) : num_points_{points.size()} {
    points_ = std::vector<Point>();
    for (size_t i = 0; i < points.size(); ++i) {
        points_.push_back(points[i]);
    }
}

geometry::Polygon& geometry::Polygon::Move(const geometry::Vector& vector) {
    for (size_t i = 0; i < num_points_; ++i) {
        points_[i].SetX(points_[i].GetX() + vector.GetX());
        points_[i].SetY(points_[i].GetY() + vector.GetY());
    }
    return *this;
}

bool geometry::Polygon::ContainsPoint(const geometry::Point& point) const {
    geometry::Ray ray = geometry::Ray(point, Point(point.GetX() + 2, point.GetY()));
    int cnt_segments = 0;
    for (int i = 0; i < num_points_; ++i) {
        geometry::Segment segment = i == 0 ? geometry::Segment(points_[num_points_ - 1], points_[i])
                                           : geometry::Segment(points_[i - 1], points_[i]);
        if (segment.ContainsPoint(point)) {
            return true;
        }
        if (segment.GetStart().GetY() == segment.GetEnd().GetY()) {
            continue;
        }
        if ((ray.ContainsPoint(segment.GetStart()) && segment.GetStart().GetY() > segment.GetEnd().GetY()) ||
            (ray.ContainsPoint(segment.GetEnd()) && segment.GetStart().GetY() < segment.GetEnd().GetY())) {
            continue;
        }
        cnt_segments += ray.CrossesSegment(segment);
    }
    return cnt_segments % 2 != 0;
}

bool geometry::Polygon::CrossesSegment(const geometry::Segment& segment) const {
    for (int i = 0; i < num_points_; ++i) {
        geometry::Segment segment1 = i == 0 ? geometry::Segment(points_[num_points_ - 1], points_[i])
                                            : geometry::Segment(points_[i - 1], points_[i]);
        if (segment.CrossesSegment(segment1)) {
            return true;
        }
    }
    return false;
}

geometry::Polygon* geometry::Polygon::Clone() const {
    return new geometry::Polygon(points_);
}
