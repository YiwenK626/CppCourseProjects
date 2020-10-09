#include "point.hpp"

#include <cmath>
#include <cstdio>
#include <cstdlib>

void Point::move(double dx, double dy) {
  x += dx;
  y += dy;
}

double Point::distanceFrom(const Point & p) {
  double dis;
  double X = p.x - x;
  double Y = p.y - y;
  dis = std::sqrt(X * X + Y * Y);
  return dis;
}
