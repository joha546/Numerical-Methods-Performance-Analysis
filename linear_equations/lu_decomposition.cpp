#include <vector>
#include <cmath>
#include <stdexcept>
#include <algorithm>
using namespace std;

void luDecomposition(vector<vector<double>>& A, vector<vector<double>>& L, vector<vector<double>>& U) {
    int n = A.size();
    L = vector<vector<double>>(n, vector<double>(n, 0));
    U = A;

    for (int i = 0; i < n; i++) {
        L[i][i] = 1;

        // Pivoting
        int maxRow = i;
        for (int k = i + 1; k < n; k++) {
            if (fabs(U[k][i]) > fabs(U[maxRow][i])) {
                maxRow = k;
            }
        }

        if (i != maxRow) {
            swap(U[i], U[maxRow]);
            swap(L[i], L[maxRow]);
        }

        // Decomposition
        for (int j = i + 1; j < n; j++) {
            if (U[i][i] == 0) {
                throw runtime_error("Zero pivot element encountered.");
            }
            L[j][i] = U[j][i] / U[i][i];
            for (int k = i; k < n; k++) {
                U[j][k] -= L[j][i] * U[i][k];
            }
        }
    }
}

vector<double> solveLU(vector<vector<double>>& L, vector<vector<double>>& U, vector<double>& b) {
    int n = L.size();
    vector<double> y(n), x(n);

    // Forward substitution (Ly = b)
    for (int i = 0; i < n; i++) {
        y[i] = b[i];
        for (int j = 0; j < i; j++) {
            y[i] -= L[i][j] * y[j];
        }
    }

    // Back substitution (Ux = y)
    for (int i = n - 1; i >= 0; i--) {
        x[i] = y[i];
        for (int j = i + 1; j < n; j++) {
            x[i] -= U[i][j] * x[j];
        }
        if (U[i][i] == 0) {
            throw runtime_error("Division by zero in back substitution.");
        }
        x[i] /= U[i][i];
    }

    return x;
}
