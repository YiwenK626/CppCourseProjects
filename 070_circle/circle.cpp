#include "circle.hpp"

#include <cmath>
using namespace std;
#include <cstdio>
#include <cstdlib>

void Circle::move(double dx, double dy) {
  center.move(dx, dy);
}

double Circle::intersectionArea(const Circle & otherCircle) {
  double area;
  double dis;

  dis = center.distanceFrom(otherCircle.center);

  if (dis >= radius + otherCircle.radius) {
    return area = 0;
  }
  if (dis <= abs(radius - otherCircle.radius)) {
    if (radius <= otherCircle.radius) {
      return area = 2 * acos(0.0) * radius * radius;
    }
    else {
      return area = 2 * acos(0.0) * otherCircle.radius * otherCircle.radius;
    }
  }
  else {
    double theta =
        2 * acos((radius * radius + dis * dis - otherCircle.radius * otherCircle.radius) /
                 (2 * dis * radius));
    double othertheta =
        2 * acos((otherCircle.radius * otherCircle.radius + dis * dis - radius * radius) /
                 (2 * dis * otherCircle.radius));
    double A_sec = 0.5 * theta * radius * radius +
                   0.5 * othertheta * otherCircle.radius * otherCircle.radius;
    double A_tri = 0.5 * sin(theta) * radius * radius +
                   0.5 * sin(othertheta) * otherCircle.radius * otherCircle.radius;
    //printf("%.2f,%.2f,%.2f,%.2f", theta, othertheta, A_sec, A_tri);
    return area = A_sec - A_tri;
  }
}
