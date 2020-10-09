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
  dis = std::sqrt(p.x * p.x + p.y * p.y);
  return dis;
}
