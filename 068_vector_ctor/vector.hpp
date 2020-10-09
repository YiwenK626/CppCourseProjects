/* write your class interface in this file
   write function definitions only if they are very short
 */

#include <cmath>
#include <cstdio>
#include <cstdlib>

class Vector2D {
 private:
  double x;
  double y;

 public:
  Vector2D() : x(0), y(0) {}
  Vector2D(double a, double b) : x(a), y(b) {}
  double getMagnitude() const {
    double mag = std::sqrt(x * x + y * y);
    return mag;
  }
  Vector2D operator+(const Vector2D & rhs) const {
    Vector2D ans;
    ans.x = x + rhs.x;
    ans.y = y + rhs.y;
    return ans;
  }
  Vector2D & operator+=(const Vector2D & rhs) {
    this->x = this->x + rhs.x;
    this->y = this->y + rhs.y;
    return *this;
  }
  double dot(const Vector2D & rhs) const {
    double dot = x * rhs.x + y * rhs.y;
    return dot;
  }
  void print() const { std::printf("<%.2f, %.2f>", x, y); }
};
