#include <math.h>

#include <cstdio>
#include <cstdlib>

#include "function.h"

int binarySearchForZero(Function<int, int> * f, int low, int high);

class CountedIntFn : public Function<int, int> {
 protected:
  unsigned remaining;
  Function<int, int> * f;
  const char * mesg;

 public:
  CountedIntFn(unsigned n, Function<int, int> * fn, const char * m) :
      remaining(n),
      f(fn),
      mesg(m) {}
  virtual int invoke(int arg) {
    if (remaining == 0) {
      fprintf(stderr, "Too many function invocations in %s\n", mesg);
      exit(EXIT_FAILURE);
    }
    remaining--;
    return f->invoke(arg);
  }
};

void check(Function<int, int> * f,
           int low,
           int high,
           int expected_ans,
           const char * mesg) {
  int remaining;  //invokation at most
  if (high > low) {
    remaining = log2(high - low) + 1;
    printf("%d", remaining);
  }
  else {
    remaining = 1;
  }
  // wrap a function with its remaining and mesg
  CountedIntFn * df = new CountedIntFn(remaining, f, mesg);

  // check if the  calculation is correct and the invokation is correct
  if (binarySearchForZero(df, low, high) != expected_ans) {
    printf("%d\n", binarySearchForZero(df, low, high));
    fprintf(stderr, "Wrong calculation in %s\n", mesg);
    exit(EXIT_FAILURE);
  }
}

class SinFunction : public Function<int, int> {
 public:
  virtual int invoke(int arg) { return 10000000 * (sin(arg / 100000.0) - 0.5); }
};

class allPFunction : public Function<int, int> {
 public:
  virtual int invoke(int arg) { return 1; }
};

class allNFunction : public Function<int, int> {
 public:
  virtual int invoke(int arg) { return -1; }
};

class linearFunction : public Function<int, int> {
 public:
  virtual int invoke(int arg) { return arg; }
};

int main() {
  SinFunction f1;
  check(&f1, 0, 150000, 52359, "SinFunction");
  allPFunction f2;
  check(&f2, -20, 20, -20, "all positive");
  allNFunction f3;
  check(&f3, -20, 20, 19, "all negative");
  linearFunction f4;
  check(&f4, -1, 1, 0, "linear with zero point");
  check(&f4, -5, -2, -3, "linear with no zero point");
  check(&f4, 2, 5, 2, "linear with no zero point");
  check(&f4, -2, 5, 0, "odd midpoint");
}
