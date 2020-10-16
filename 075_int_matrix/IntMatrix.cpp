#include "IntMatrix.h"

IntMatrix::IntMatrix() : numRows(0), numColumns(0) {
}
IntMatrix::IntMatrix(int r, int c) : numRows(r), numColumns(c) {
  rows = new IntArray *[r];
  for (int n = 0; n < r; n++) {
    rows[n] = new IntArray(c);
  }
}
IntMatrix::IntMatrix(const IntMatrix & rhs) :
    numRows(rhs.numRows),
    numColumns(rhs.numColumns) {
  rows = new IntArray *[rhs.numRows];
  for (int n = 0; n < rhs.numRows; n++) {
    rows[n] = new IntArray(rhs.numColumns);
  }
  for (int i = 0; i < numRows; i++) {
    *rows[i] = *rhs.rows[i];
  }
}
IntMatrix::~IntMatrix() {
  for (int i = 0; i < numRows; i++) {
    delete rows[i];
  }
  delete[] rows;
}
IntMatrix & IntMatrix::operator=(const IntMatrix & rhs) {
  this->numColumns = rhs.numColumns;
  this->numRows = rhs.numRows;
  this->rows = new IntArray *[rhs.numRows];
  for (int n = 0; n < rhs.numRows; n++) {
    rows[n] = new IntArray(numColumns);
  }
  for (int i = 0; i < numRows; i++) {
    *rows[i] = *rhs.rows[i];
  }
  return *this;
}

int IntMatrix::getRows() const {
  return numRows;
}
int IntMatrix::getColumns() const {
  return numColumns;
}
const IntArray & IntMatrix::operator[](int index) const {
  assert(index < numRows);
  return *rows[index];
}
IntArray & IntMatrix::operator[](int index) {
  assert(index < numRows);
  return *rows[index];
}

bool IntMatrix::operator==(const IntMatrix & rhs) const {
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

IntMatrix IntMatrix::operator+(const IntMatrix & rhs) const {
  assert(numColumns == rhs.numColumns && numRows == rhs.numRows);
  for (int i = 0; i < numRows; i++) {
    assert(rows[i]->size() == rhs.rows[i]->size());
  }
  IntMatrix sum(numRows, numColumns);
  for (int i = 0; i < numRows; i++) {
    for (int k = 0; k < rows[i]->size(); k++) {
      sum[i][k] = (*this)[i][k] + rhs[i][k];
    }
  }
  return sum;
}

std::ostream & operator<<(std::ostream & s, const IntMatrix & rhs) {
  s << "[ ";
  int i;
  if (rhs.getRows() >= 1) {
    for (i = 0; i < rhs.getRows(); i++) {
      s << rhs[i];

      if (i != rhs.getRows() - 1) {
        s << "\n";
      }
    }
  }
  s << " ]";
  return s;
}
