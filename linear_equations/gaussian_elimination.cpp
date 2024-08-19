#include <vector>
#include <cmath>
#include <stdexcept>
#include <algorithm>
using namespace std;


vector<double> gaussianElimination(vector<vector<double>>& A, vector<double>& b) {
    int n = A.size();

    // Check if dimensions match
    if (n != b.size()) {
        throw invalid_argument("Matrix A and vector b dimensions do not match.");
    }

    for (int i = 0; i < n; i++) {
        // Find the pivot row
        int maxRow = i;
        for (int k = i + 1; k < n; k++) {
            if (fabs(A[k][i]) > fabs(A[maxRow][i])) {
                maxRow = k;
            }
        }

        // Swap rows if necessary
        if (i != maxRow) {
            swap(A[i], A[maxRow]);
            swap(b[i], b[maxRow]);
        }

        // Check for zero pivot element
        if (fabs(A[i][i]) < 1e-12) {
            throw runtime_error("Zero pivot element encountered.");
        }

        // Forward elimination
        for (int j = i + 1; j < n; j++) {
            double factor = A[j][i] / A[i][i];
            for (int k = i; k < n; k++) {
                A[j][k] -= factor * A[i][k];
            }
            b[j] -= factor * b[i];
        }
    }

    // Back substitution
    std::vector<double> x(n);
    for (int i = n - 1; i >= 0; i--) {
        x[i] = b[i];
        for (int j = i + 1; j < n; j++) {
            x[i] -= A[i][j] * x[j];
        }
        x[i] /= A[i][i];
    }

    return x;
}
