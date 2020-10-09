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
  void initVector(double init_x, double init_y) {
    x = init_x;
    y = init_y;
  }

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
