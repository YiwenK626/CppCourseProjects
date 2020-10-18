#ifndef __T_MATRIX_H___
#define __T_MATRIX_H___

#include <assert.h>

#include <cstdlib>
#include <iostream>
#include <vector>

//YOUR CODE GOES HERE!
template<typename T>
class Matrix {
 private:
  int numRows;
  int numColumns;
  std::vector<T> ** rows;

 public:
  Matrix() : numRows(0), numColumns(0) {}
  Matrix(int r, int c) : numRows(r), numColumns(c) {
    rows = new std::vector<T> *[r]();
    for (int n = 0; n < r; n++) {
      rows[n] = new std::vector<T>(c);
    }
  }
  Matrix(const Matrix & rhs) : numRows(rhs.numRows), numColumns(rhs.numColumns) {
    rows = new std::vector<T> *[rhs.numRows]();
    for (int n = 0; n < rhs.numRows; n++) {
      rows[n] = new std::vector<T>(numColumns);
    }
    for (int i = 0; i < numRows; i++) {
      *rows[i] = *rhs.rows[i];
    }
  }

  ~Matrix() {
    for (int i = 0; i < numRows; i++) {
      delete rows[i];
    }
    delete[] rows;
  }
  Matrix & operator=(const Matrix & rhs) {
    this->numColumns = rhs.numColumns;
    this->numRows = rhs.numRows;
    this->rows = new std::vector<T> *[rhs.numRows];
    for (int n = 0; n < rhs.numRows; n++) {
      rows[n] = new std::vector<T>(numColumns);
    }
    for (int i = 0; i < numRows; i++) {
      *rows[i] = *rhs.rows[i];
    }
    return *this;
  }

  int getRows() const { return numRows; }
  int getColumns() const { return numColumns; }
  const std::vector<T> & operator[](int index) const {
    assert(index < numRows);
    assert(index >= 0);
    return *rows[index];
  }
  std::vector<T> & operator[](int index) {
    assert(index < numRows);
    assert(index > 0);
    return *rows[index];
  }

  bool operator==(const Matrix & rhs) const {
    if (numColumns != rhs.numColumns || numRows != rhs.numRows) {
      return false;
    }
    else {
      for (int i = 0; i < numRows; i++) {
        for (int j = 0; j < numColumns; j++) {
          if ((*this)[i][j] != rhs[i][j]) {
            return false;
          }
        }
      }
    }
    return true;
  }

  Matrix operator+(const Matrix & rhs) const {
    assert(this->numColumns == rhs.numColumns);
    assert(this->numRows == rhs.numRows);
    for (int i = 0; i < numRows; i++) {
      assert(rows[i]->size() == rhs.rows[i]->size());
    }
    Matrix sum(numRows, numColumns);
    for (int i = 0; i < numRows; i++) {
      for (unsigned int k = 0; k < rows[i]->size(); k++) {
        sum[i][k] = (*this)[i][k] + rhs[i][k];
      }
    }
    return sum;
  }
};

template<typename A>
std::ostream & operator<<(std::ostream & s, const Matrix<A> & rhs) {
  s << "[ ";
  int i;
  int j;
  if (rhs.getRows() >= 1) {
    for (i = 0; i < rhs.getRows(); i++) {
      typename std::vector<A>::const_iterator it = rhs[i].begin();
      j = 0;
      s << "{";
      while (it != rhs[i].end()) {
        if (j > 0) {
          s << ", ";
        }
        s << *it;
        j++;
        ++it;
      }
      s << "}";
      if (i != rhs.getRows() - 1) {
        s << ",\n";
      }
    }
  }
  s << " ]";
  return s;
}

#endif
