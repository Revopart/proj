#include "s21_matrix_oop.hpp"

void S21Matrix::DeleteMatrix() {
  if (matrix_ != nullptr) {
    for (int i = 0; i < rows_; i++) {
      delete[] matrix_[i];
    }
    delete[] matrix_;
  }
}

void S21Matrix::CreateMatrix(int rows_, int cols_) {
  this->matrix_ = new double *[rows_]();
  for (int i = 0; i < rows_; i++) {
    this->matrix_[i] = new double[cols_];
  }
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      this->matrix_[i][j] = 0.0;
    }
  }
}

S21Matrix::S21Matrix() {
  rows_ = 0;
  cols_ = 0;
  CreateMatrix(rows_, cols_);
}

S21Matrix::S21Matrix(int rows, int cols) {
  rows_ = rows;
  cols_ = cols;
  if (cols_ <= 0 || rows_ <= 0) {
    throw std::invalid_argument("rows or columns equal or less 0");
  } else {
    CreateMatrix(rows_, cols_);
  }
}

S21Matrix::S21Matrix(const S21Matrix &other) {
  rows_ = other.rows_;
  cols_ = other.cols_;
  CreateMatrix(other.rows_, other.cols_);
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] = other.matrix_[i][j];
    }
  }
}

S21Matrix::S21Matrix(S21Matrix &&other) {
  rows_ = other.rows_;
  cols_ = other.cols_;
  CreateMatrix(rows_, cols_);
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] = other.matrix_[i][j];
    }
  }
}

S21Matrix::~S21Matrix() {
  this->DeleteMatrix();
  rows_ = 0;
  cols_ = 0;
}

bool S21Matrix::EqMatrix(const S21Matrix &other) {
  int res = true;
  if (cols_ == other.cols_ && rows_ == other.rows_ && matrix_ != nullptr &&
      other.matrix_ != nullptr) {
    for (int i = 0; i < rows_; i++) {
      for (int j = 0; j < cols_; j++) {
        if (fabs(matrix_[i][j] - other.matrix_[i][j]) > EPS) {
          res = false;
          break;
        }
      }
    }
  } else {
    res = false;
  }
  return res;
}

void S21Matrix::SumMatrix(const S21Matrix &other) {
  if (rows_ != other.rows_ || cols_ != other.cols_)
    throw std::runtime_error("Invalid matrix dimensions");
  else {
    for (int i = 0; i < rows_; i++) {
      for (int j = 0; j < cols_; j++) {
        matrix_[i][j] += other.matrix_[i][j];
      }
    }
  }
}
void S21Matrix::SubMatrix(const S21Matrix &other) {
  if (rows_ != other.rows_ || cols_ != other.cols_)
    throw std::runtime_error("Invalid matrix dimensions");
  else {
    for (int i = 0; i < rows_; i++) {
      for (int j = 0; j < cols_; j++) {
        matrix_[i][j] -= other.matrix_[i][j];
      }
    }
  }
}
void S21Matrix::MulNumber(const double num) {
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] *= num;
    }
  }
}
void S21Matrix::MulMatrix(const S21Matrix &other) {
  if (cols_ != other.rows_) {
    throw std::runtime_error("invalid dimension");
  }
  S21Matrix buf(rows_, other.cols_);
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < other.cols_; j++) {
      for (int k = 0; k < cols_; k++) {
        buf.matrix_[i][j] += matrix_[i][k] * other.matrix_[k][j];
      }
    }
  }
  *this = buf;
}

S21Matrix S21Matrix::Transpose() {
  S21Matrix temp(cols_, rows_);
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      temp.matrix_[j][i] = matrix_[i][j];
    }
  }
  return temp;
}

double S21Matrix::Determinant() {
  double determinant = 0.0;
  if (rows_ == 1) {
    determinant = this->matrix_[0][0];
  } else {
    S21Matrix new_matrix(rows_ - 1, cols_ - 1);
    for (int j = 0; j < cols_; ++j) {
      for (int i = 1; i < rows_; ++i) {
        for (int k = 0; k < cols_; ++k) {
          if (k < j) {
            new_matrix.matrix_[i - 1][k] = matrix_[i][k];
          } else if (k > j) {
            new_matrix.matrix_[i - 1][k - 1] = matrix_[i][k];
          }
        }
      }
      determinant +=
          ((j % 2 == 0) ? 1 : -1) * matrix_[0][j] * new_matrix.Determinant();
    }
  }
  return determinant;
}

S21Matrix S21Matrix::CalcComplements() {
  if (cols_ != rows_) {
    throw std::invalid_argument("not nxn");
  }

  S21Matrix result(rows_, cols_);
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      S21Matrix temp_matrix(rows_ - 1, cols_ - 1);
      CropMatrix_(i, j, temp_matrix);
      double temp = temp_matrix.Determinant();
      result.matrix_[i][j] = ((i + j) % 2 == 0 ? 1 : -1) * temp;
    }
  }
  return result;
}

S21Matrix S21Matrix::InverseMatrix() {
  double det = this->Determinant();
  if (fabs(det) < 1e-6) {
    throw std::invalid_argument("zero det.");
  }
  S21Matrix result = this->CalcComplements();
  result = result.Transpose();

  for (int i = 0; i < result.rows_; i++) {
    for (int j = 0; j < result.cols_; j++) {
      result.matrix_[i][j] = result.matrix_[i][j] / det;
    }
  }
  return result;
}

void S21Matrix::CropMatrix_(int del_row, int del_col, S21Matrix &other) {
  for (int i = 0; i < other.rows_; i++) {
    if (i == del_row) continue;
    for (int j = 0; j < other.cols_; j++) {
      if (j == del_col) continue;
      other.matrix_[i - (i > del_row)][j - (j > del_col)] = matrix_[i][j];
    }
  }
}

S21Matrix S21Matrix::operator+(const S21Matrix &other) {
  S21Matrix result(*this);
  result.SumMatrix(other);
  return result;
}

S21Matrix S21Matrix::operator-(const S21Matrix &other) {
  S21Matrix result(*this);
  result.SubMatrix(other);
  return result;
}

S21Matrix S21Matrix::operator*(const S21Matrix &other) {
  S21Matrix result(*this);
  result.MulMatrix(other);
  return result;
}

S21Matrix S21Matrix::operator*(const double &number) {
  S21Matrix result(*this);
  result.MulNumber(number);
  return result;
}

S21Matrix &S21Matrix::operator-=(const S21Matrix &other) {
  this->SubMatrix(other);
  return *this;
}

S21Matrix &S21Matrix::operator+=(const S21Matrix &other) {
  this->SumMatrix(other);
  return *this;
}

S21Matrix &S21Matrix::operator*=(const S21Matrix &other) {
  this->MulMatrix(other);
  return *this;
}

S21Matrix &S21Matrix::operator*=(const double &number) {
  this->MulNumber(number);
  return *this;
}

bool S21Matrix::operator==(const S21Matrix &other) { return EqMatrix(other); }

S21Matrix &S21Matrix::operator=(const S21Matrix &other) {
  if (this == &other) {
    return *this;
  }

  if (matrix_ != nullptr) {
    DeleteMatrix();
  }

  rows_ = other.rows_;
  cols_ = other.cols_;
  CreateMatrix(rows_, cols_);

  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      this->matrix_[i][j] = other.matrix_[i][j];
    }
  }

  return *this;
}

double &S21Matrix::operator()(int row, int col) {
  if (row >= this->rows_ || col >= this->cols_ || row < 0 || col < 0) {
    throw std::invalid_argument("Index is outside the matrix ERROR!");
  }
  return this->matrix_[row][col];
}

int S21Matrix::GetRows() { return rows_; }
int S21Matrix::GetCols() { return cols_; }
void S21Matrix::SetRows(const int &rows) {
  S21Matrix new_matrix(rows, cols_);
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols_; j++) {
      if (i < rows_ - 1) {
        new_matrix.matrix_[i][j] = matrix_[i][j];
      } else {
        new_matrix.matrix_[i][j] = 0;
      }
    }
  }
  this->DeleteMatrix();
  *this = new_matrix;
}

void S21Matrix::SetCols(const int &cols) {
  S21Matrix new_matrix(rows_, cols);
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols; j++) {
      if (j < cols_ - 1) {
        new_matrix.matrix_[i][j] = matrix_[i][j];
      } else {
        new_matrix.matrix_[i][j] = 0;
      }
    }
  }
  this->DeleteMatrix();
  *this = new_matrix;
}