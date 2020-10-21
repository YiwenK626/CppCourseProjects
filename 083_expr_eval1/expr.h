#define __EXPR_H__

#include <iostream>
#include <sstream>
class Expression {
 public:
  virtual std::string toString() const = 0;
  virtual ~Expression(){};
};

class NumExpression : public Expression {
  long int Num;

 public:
  NumExpression(long num) : Num(num) {}
  virtual std::string toString() const {
    std::stringstream str;
    str << Num;

    std::string expr;
    str >> expr;
    return expr;
  }
  virtual ~NumExpression(){};
};

class PlusExpression : public Expression {
  Expression * lhs;
  Expression * rhs;

 public:
  PlusExpression(Expression * lhs, Expression * rhs) : lhs(lhs), rhs(rhs) {}
  virtual std::string toString() const {
    std::ostringstream str;

    str << "(" << lhs->toString() << " + " << rhs->toString() << ")";

    return str.str();
  }
  virtual ~PlusExpression(){};
};
