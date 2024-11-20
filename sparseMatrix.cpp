#include <iostream>
using namespace std;

struct Cell {
    int row, col, value;
    Cell* nextRow;
    Cell* nextCol;

    Cell(int r, int c, int v) : row(r), col(c), value(v), nextRow(this), nextCol(this) {}
};

class SparseMatrix {
private:
    Cell* head; // Nodo centinela
    int rows, cols;

    // Buscar celda específica
    Cell* findCell(int row, int col) {
        Cell* curr = head->nextRow;
        while (curr != head) {
            if (curr->row == row && curr->col == col) return curr;
            curr = curr->nextRow;
        }
        return nullptr; // No encontrada
    }

public:
    SparseMatrix(int r, int c) : rows(r), cols(c) {
        head = new Cell(-1, -1, 0); // Centinela
        head->nextRow = head;
        head->nextCol = head;
    }

    ~SparseMatrix() {
        Cell* rowCurr = head->nextRow;
        while (rowCurr != head) {
            Cell* colCurr = rowCurr;
            while (colCurr->nextCol != rowCurr) {
                Cell* toDelete = colCurr;
                colCurr = colCurr->nextCol;
                delete toDelete;
            }
            Cell* toDelete = rowCurr;
            rowCurr = rowCurr->nextRow;
            delete toDelete;
        }
        delete head;
    }

    void insert(int row, int col, int value) {
        if (row < 0 || row >= rows || col < 0 || col >= cols || value == 0) return;

        Cell* existing = findCell(row, col);
        if (existing) {
            existing->value = value; // Actualizar valor existente
            return;
        }

        Cell* newCell = new Cell(row, col, value);

        // Insertar en la fila
        Cell* rowPrev = head;
        Cell* rowCurr = head->nextRow;
        while (rowCurr != head && rowCurr->row < row) {
            rowPrev = rowCurr;
            rowCurr = rowCurr->nextRow;
        }
        while (rowCurr != head && rowCurr->row == row && rowCurr->col < col) {
            rowPrev = rowCurr;
            rowCurr = rowCurr->nextCol;
        }
        newCell->nextCol = rowCurr;
        rowPrev->nextCol = newCell;

        // Insertar en la columna
        Cell* colPrev = head;
        Cell* colCurr = head->nextCol;
        while (colCurr != head && colCurr->col < col) {
            colPrev = colCurr;
            colCurr = colCurr->nextCol;
        }
        while (colCurr != head && colCurr->col == col && colCurr->row < row) {
            colPrev = colCurr;
            colCurr = colCurr->nextRow;
        }
        newCell->nextRow = colCurr;
        colPrev->nextRow = newCell;
    }

    void remove(int row, int col) {
        Cell* target = findCell(row, col);
        if (!target) return;

        // Eliminar de la fila
        Cell* rowPrev = head;
        Cell* rowCurr = head->nextRow;
        while (rowCurr != target) {
            rowPrev = rowCurr;
            rowCurr = rowCurr->nextCol;
        }
        rowPrev->nextCol = rowCurr->nextCol;

        // Eliminar de la columna
        Cell* colPrev = head;
        Cell* colCurr = head->nextCol;
        while (colCurr != target) {
            colPrev = colCurr;
            colCurr = colCurr->nextRow;
        }
        colPrev->nextRow = colCurr->nextRow;

        delete target;
    }

    int operator()(int row, int col) {
        Cell* target = findCell(row, col);
        return target ? target->value : 0;
    }

    bool compare(const SparseMatrix& other) {
        if (rows != other.rows || cols != other.cols) return false;

        Cell* curr = head->nextRow;
        Cell* otherCurr = other.head->nextRow;

        while (curr != head && otherCurr != head) {
            if (curr->row != otherCurr->row || curr->col != otherCurr->col || curr->value != otherCurr->value)
                return false;

            curr = curr->nextRow;
            otherCurr = otherCurr->nextRow;
        }
        return curr == head && otherCurr == head;
    }

    SparseMatrix add(const SparseMatrix& other) {
        SparseMatrix result(rows, cols);
        Cell* curr = head->nextRow;
        while (curr != head) {
            result.insert(curr->row, curr->col, curr->value);
            curr = curr->nextRow;
        }
        Cell* otherCurr = other.head->nextRow;
        while (otherCurr != head) {
            int sum = result(otherCurr->row, otherCurr->col) + otherCurr->value;
            result.insert(otherCurr->row, otherCurr->col, sum);
            otherCurr = otherCurr->nextRow;
        }
        return result;
    }

    SparseMatrix subtract(const SparseMatrix& other) {
        SparseMatrix result(rows, cols);
        Cell* curr = head->nextRow;
        while (curr != head) {
            result.insert(curr->row, curr->col, curr->value);
            curr = curr->nextRow;
        }
        Cell* otherCurr = other.head->nextRow;
        while (otherCurr != head) {
            int diff = result(otherCurr->row, otherCurr->col) - otherCurr->value;
            result.insert(otherCurr->row, otherCurr->col, diff);
            otherCurr = otherCurr->nextRow;
        }
        return result;
    }

    SparseMatrix transpose() {
        SparseMatrix result(cols, rows);
        Cell* curr = head->nextRow;
        while (curr != head) {
            result.insert(curr->col, curr->row, curr->value);
            curr = curr->nextRow;
        }
        return result;
    }

    SparseMatrix multiply(const SparseMatrix& other) {
        if (cols != other.rows) return SparseMatrix(0, 0); // Dimensiones incompatibles

        SparseMatrix result(rows, other.cols);
        Cell* curr = head->nextRow;

        while (curr != head) {
            Cell* otherCurr = other.head->nextRow;
            while (otherCurr != head) {
                if (curr->col == otherCurr->row) {
                    int product = curr->value * otherCurr->value;
                    result.insert(curr->row, otherCurr->col, result(curr->row, otherCurr->col) + product);
                }
                otherCurr = otherCurr->nextRow;
            }
            curr = curr->nextRow;
        }
        return result;
    }

    void display() {
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                cout << (*this)(i, j) << " ";
            }
            cout << endl;
        }
    }
};

int main() {
    SparseMatrix mat(3, 3);
    mat.insert(0, 0, 1);
    mat.insert(1, 1, 2);
    mat.insert(2, 2, 3);

    SparseMatrix mat2(3, 3);
    mat2.insert(0, 0, 4);
    mat2.insert(1, 1, 5);
    mat2.insert(2, 2, 6);

    cout << "Matriz 1:" << endl;
    mat.display();

    cout << "Matriz 2:" << endl;
    mat2.display();

    SparseMatrix result = mat.add(mat2);
    cout << "Suma:" << endl;
    result.display();

    return 0;
}
