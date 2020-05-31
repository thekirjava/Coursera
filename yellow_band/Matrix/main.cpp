#include <iostream>
#include <vector>
#include <stdexcept>

using namespace std;

class Matrix {
public:
    friend std::istream &operator>>(std::istream &in, Matrix &matrix) {
        in >> matrix.rows >> matrix.cols;
        matrix.Reset(matrix.rows, matrix.cols);
        for (int i = 0; i < matrix.rows; i++) {
            for (int j = 0; j < matrix.cols; j++) {
                in >> matrix.mat[i][j];
            }
        }
        return in;
    }

    friend std::ostream &operator<<(std::ostream &out, const Matrix &matrix) {
        out << matrix.rows << " " << matrix.cols << '\n';
        for (int i = 0; i < matrix.rows; i++) {
            for (int j = 0; j < matrix.cols; j++) {
                if (j > 0) {
                    out << " ";
                }
                out << matrix.mat[i][j];
            }
            out << '\n';
        }
        return out;
    }

    friend bool operator==(const Matrix &matrix1, const Matrix &matrix2) {
        if (((matrix1.rows == matrix2.rows) && (matrix1.cols == matrix2.cols)) ||
            (((matrix1.rows == 0) || (matrix1.cols == 0)) && ((matrix2.rows == 0) || (matrix2.cols == 0)))) {
            if ((matrix1.rows == 0) || (matrix1.cols == 0)) {
                return true;
            }
            for (int i = 0; i < matrix1.rows; i++) {
                for (int j = 0; j < matrix1.cols; j++) {
                    if (matrix1.mat[i][j] != matrix2.mat[i][j]) {
                        return false;
                    }
                }
            }
            return true;
        }
        return false;
    }

    friend Matrix operator+(const Matrix &matrix1, const Matrix &matrix2) {
        if (((matrix1.rows == matrix2.rows) && (matrix1.cols == matrix2.cols)) ||
            (((matrix1.rows == 0) || (matrix1.cols == 0)) && ((matrix2.rows == 0) || (matrix2.cols == 0)))) {
            if ((matrix1.rows == 0) || (matrix1.cols == 0)) {
                return Matrix();
            }
            Matrix ans(matrix1.rows, matrix1.cols);
            for (int i = 0; i < matrix1.rows; i++) {
                for (int j = 0; j < matrix1.cols; j++) {
                    ans.mat[i][j] = matrix1.mat[i][j] + matrix2.mat[i][j];
                }
            }
            return ans;
        }
        throw std::invalid_argument("invalid argument");
    }

    Matrix() {
        rows = 0;
        cols = 0;
    }

    Matrix(int num_rows, int num_cols) {
        if ((num_cols < 0) || (num_rows < 0)) {
            throw std::out_of_range("out of range");
        }
        mat.resize(num_rows, std::vector<int>(num_cols, 0));
        rows = num_rows;
        cols = num_cols;
    }

    void Reset(int num_rows, int num_cols) {
        if ((num_cols < 0) || (num_rows < 0)) {
            throw std::out_of_range("out of range");
        }
        mat.clear();
        mat.resize(num_rows, std::vector<int>(num_cols, 0));
        rows = num_rows;
        cols = num_cols;
    }

    int At(int row_pos, int col_pos) const {
        if ((row_pos < 0) || (row_pos >= rows) || (col_pos < 0) || (col_pos >= cols)) {
            throw std::out_of_range("out of range");
        }
        return mat[row_pos][col_pos];
    }

    int &At(int row_pos, int col_pos) {
        if ((row_pos < 0) || (row_pos >= rows) || (col_pos < 0) || (col_pos >= cols)) {
            throw std::out_of_range("Out of range");
        }
        return mat[row_pos][col_pos];
    }

    int GetNumRows() const {
        return rows;
    }

    int GetNumColumns() const {
        return cols;
    }

private:
    std::vector<std::vector<int> > mat;
    int rows;
    int cols;
};

int main() {
    Matrix one;
    Matrix two;

    std::cin >> one >> two;
    std::cout << one + two << std::endl;
    return 0;
}