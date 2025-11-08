#include <iostream>

int* resize(const int* a, size_t k, size_t d, int filler);
int* transpon(const int* a, size_t n, size_t m);

size_t getLen(const int* a, const int* b)
{
  size_t t = 0;
  size_t i = 0;
  while (a[i] != '\0') {
    ++t;
    ++i;
  }
  if (b == nullptr) {
    return t;
  }
  i = 0;
  while (b[i] !='\0') {
    ++t;
    ++i;
  }
  return t;
}

void show_matrix(int** a, size_t n, size_t m)
{
  for (size_t i = 0; i < n; ++i) {
    for (size_t j = 0; j < getLen(a[i], nullptr); ++j) {
      std::cout << a[i][j] <<'\t';
    }
    std::cout << '\n';
  }
}
void deleting(int** mat, size_t created)
{
  for (size_t i = 0; i < created; i++) {
    delete[] mat[i];
  }
  delete[] mat;
}



int** concat_rows(const int* const* lhs, size_t n1, size_t m1,
const int* const* rhs, size_t n2, size_t m2)
{
  size_t newRows = std::max(n1,n2);
  int** matr = new int*[newRows];
  for (size_t i = 0; i < newRows; ++i) {
    try {
      matr[i] = new int[getLen(lhs[i], rhs[i])]{};
    } catch (const std::bad_alloc &e) {
      deleting(matr, i);
      throw;
    }
  }

  for (size_t i = 0; i < n1; ++i) {
    for (size_t j = 0; j < m1; ++j) {
      matr[i][j] = lhs[i][j];
    }
  }

  for (size_t i = 0; i < n2; ++i) {
    for (size_t j = 0; j < m2; ++j) {
      if (i < n1) {
        matr[i][j+m1] = rhs[i][j];
      } else {
        matr[i][j] = rhs[i][j];
      }
    }
  }
  show_matrix(matr, newRows, m1+m2);

  return matr;
}


int main()
{
  int** a = new int*[2];
  int** b = new int*[3];


  a[0] = new int[3]{1,2,3};
  a[1] = new int[3]{6,7,8};

  b[0] = new int[3]{4,5,6};
  b[1] = new int[3]{9,10,11};
  b[2] = new int[3]{12,13,14};

  show_matrix(a, 2, 3);
  show_matrix(b, 3, 3);

  int** n = concat_rows(a, 2, 3, b, 3, 3);

  deleting(a, 2);
  deleting(b, 3);
  deleting(n, 3);

}

int* resize(const int* a, size_t k, size_t d, int filler)
{
  int* newArr = new int[d];
  if (d > k) {
    size_t i = 0;
    for (; i < k; i++) {
      newArr[i] = a[i];
    }
    for (; i < d; i++) {
      newArr[i] = filler;
    }
  } else {
    size_t i = 0;
    for (; i < d; i++) {
      newArr[i] = a[i];
    }
  }
  return newArr;
}

int* transpon(const int* a, size_t n, size_t m)
{
  int* narr = new int[n*m];
  for (size_t i = 0; i < n; ++i) {
    for (size_t j = 0; j < m; ++j) {
      narr[j*n + i] = a[i*m + j];
    }
  }
  return narr;
}
