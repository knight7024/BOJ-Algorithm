#include <bits/stdc++.h>
#define endl '\n'
using namespace std;

// N*N 행렬
class Matrix {
private:
    int n = 0;
    vector<vector<long>> matrix;
    long mod = 0;

public:
    Matrix() {}
    Matrix(int n): n(n) {
        matrix.resize(n);
        for (auto &row : matrix) row.resize(n);
    }
    Matrix(vector<vector<long>> matrix): matrix(matrix) { n = matrix.size(); }
    Matrix(const Matrix &a): n(a.size()) {
        matrix.resize(n);
        for (int i = 0; i < n; i++) matrix[i] = a.matrix[i];
    }
    Matrix(const Matrix &a, long mod): n(a.size()), mod(mod) {
        matrix.resize(n);
        for (int i = 0; i < n; i++) matrix[i] = a.matrix[i];
    }

    Matrix operator+(const Matrix& a) {
        Matrix result = Matrix(n, mod);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                long v = matrix[i][j] + a.get(i, j);
                result.set(i, j, mod ? v % mod : v);
            }
        }
        return result;
    }

    Matrix operator-(const Matrix& a) {
        Matrix result = Matrix(n, mod);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                long v = matrix[i][j] - a.get(i, j);
                result.set(i, j, mod ? v % mod : v);
            }
        }
        return result;
    }

    Matrix operator*(const Matrix& a) {
        Matrix result = Matrix(n, mod);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                long sum = 0;
                for (int k = 0; k < n; k++) {
                    if (mod) sum = (sum + ((matrix[i][k] % mod) * (a.get(k, j) % mod)) % mod) % mod;
                    else sum += matrix[i][k] * a.get(k, j);
                }
                result.set(i, j, sum);
            }
        }
        return result;
    }

    Matrix operator%(long mod) {
        Matrix result = Matrix(n, mod);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                result.set(i, j, matrix[i][j] % mod);
            }
        }
        return result;
    }

    Matrix& operator+=(const Matrix& a) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                long v = matrix[i][j] + a.get(i, j);
                set(i, j, mod ? v % mod : v);
            }
        }
        return *this;
    }

    Matrix& operator-=(const Matrix& a) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                long v = matrix[i][j] - a.get(i, j);
                set(i, j, mod ? v % mod : v);
            }
        }
        return *this;
    }

    Matrix& operator*=(const Matrix& a) {
        Matrix result(n, mod);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                long sum = 0;
                for (int k = 0; k < n; k++) {
                    if (mod) sum = (sum + ((matrix[i][k] % mod) * (a.get(k, j) % mod)) % mod) % mod;
                    else sum += matrix[i][k] * a.get(k, j);
                }
                result.set(i, j, sum);
            }
        }
        return *this = result;
    }

    Matrix& operator%=(long mod) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                set(i, j, matrix[i][j] % mod);
            }
        }
        return *this;
    }

    long get(int r, int c) const { return matrix[r][c]; }

    void set(int r, int c, long v) { matrix[r][c] = v; }

    int size() const { return n; }
};

// 단위행렬
class IdentityMatrix : public Matrix {
public:
    IdentityMatrix(int n): Matrix(n) {
        for (int i = 0; i < n; i++) Matrix::set(i, i, 1);
    }
};

ostream& operator<<(ostream& os, const Matrix &matrix) {
    for (int i = 0; i < matrix.size(); i++) {
        for (int j = 0; j < matrix.size(); j++) {
            os << matrix.get(i, j) << ' ';
        }
        os << endl;
    }
    return os;
}

Matrix pow(Matrix &matrix, long e) {
    if (!e) return IdentityMatrix(matrix.size());
    Matrix half = pow(matrix, e / 2);
    return e & 1 ? half * half * matrix : half * half;
}

Matrix pow(Matrix &matrix, long e, long mod) {
    if (!e) return Matrix(IdentityMatrix(matrix.size()), mod);
    Matrix half = pow(matrix, e / 2, mod);
    return e & 1 ? half * half * matrix : half * half;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n; long b;
    cin >> n >> b;

    Matrix answer = Matrix(n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            int num;
            cin >> num;
            answer.set(i, j, num);
        }
    }

    cout << pow(answer, b, 1000);

    return 0;
}
