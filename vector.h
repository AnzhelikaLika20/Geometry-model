#pragma once

#include <cmath>

namespace geometry {
class Vector {
private:
    int64_t x_coord_;
    int64_t y_coord_;

public:
    Vector();

    Vector(int64_t x, int64_t y);

    int64_t GetX() const;

    int64_t GetY() const;

    Vector operator+(const Vector& other) const;

    Vector operator-(const Vector& other) const;

    Vector operator+() const;

    Vector operator-() const;

    Vector operator*(int64_t number) const;

    Vector operator/(int64_t number) const;

    Vector& operator+=(const Vector& other);

    Vector& operator-=(const Vector& other);

    Vector& operator*=(int64_t number);

    Vector& operator/=(int64_t number);

    bool operator==(const Vector& other) const;

    friend int64_t ScalarMult(const geometry::Vector& first, const geometry::Vector& second) {
        return first.GetX() * second.GetX() + first.GetY() * second.GetY();
    }

    friend int64_t VectorMult(const geometry::Vector& first, const geometry::Vector& second) {
        return first.GetX() * second.GetY() - second.GetX() * first.GetY();
    }

    friend double Length(geometry::Vector vector) {
        return sqrt(static_cast<double>(vector.GetX() * vector.GetX()) +
                    static_cast<double>(vector.GetY() * vector.GetY()));
    }
};
}  // namespace geometry
