#include "linear_equation_solver.h"
#include <stdexcept>
#include <cmath>
using namespace std;

LinearEquationSolver::LinearEquationSolver(Matrix A, Vector b) : A(A), b(b) {}

Vector LinearEquationSolver::solve(int method_choice) {
    Vector x;
    switch (method_choice) {
        case 1:
            x = gaussianElimination();
            break;
        case 2:
            x = luDecomposition();
            break;
        case 3:
            x = jacobiMethod();
            break;
        case 4:
            x = gaussSeidelMethod();
            break;
        default:
            throw runtime_error("Invalid method choice");
    }
    return x;
}

Vector LinearEquationSolver::gaussianElimination() {
    // Implementation remains the same
    int n = A.size();
    Matrix augmentedMatrix(n, Vector(n + 1));

    // Form the augmented matrix [A|b]
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            augmentedMatrix[i][j] = A[i][j];
        }
        augmentedMatrix[i][n] = b[i];
    }

    // Gaussian Elimination process
    for (int i = 0; i < n; i++) {
        for (int k = i + 1; k < n; k++) {
            double factor = augmentedMatrix[k][i] / augmentedMatrix[i][i];
            for (int j = 0; j <= n; j++) {
                augmentedMatrix[k][j] -= factor * augmentedMatrix[i][j];
            }
        }
    }

    // Back Substitution
    Vector x(n);
    for (int i = n - 1; i >= 0; i--) {
        x[i] = augmentedMatrix[i][n];
        for (int j = i + 1; j < n; j++) {
            x[i] -= augmentedMatrix[i][j] * x[j];
        }
        x[i] /= augmentedMatrix[i][i];
    }
    return x;
}

Vector LinearEquationSolver::luDecomposition() {
    // Implementation remains the same
    int n = A.size();
    Matrix L(n, Vector(n, 0));
    Matrix U(n, Vector(n, 0));

        // LU Decomposition process
    for (int i = 0; i < n; i++) {
        for (int j = i; j < n; j++) {
            U[i][j] = A[i][j];
            for (int k = 0; k < i; k++) {
                U[i][j] -= L[i][k] * U[k][j];
            }
        }
        for (int j = i; j < n; j++) {
            if (i == j)
                L[i][i] = 1; // Diagonal as 1
            else {
                L[j][i] = A[j][i];
                for (int k = 0; k < i; k++) {
                    L[j][i] -= L[j][k] * U[k][i];
                }
                L[j][i] /= U[i][i];
            }
        }
    }
    // Solve Ly = b
    Vector y(n);
    for (int i = 0; i < n; i++) {
        y[i] = b[i];
        for (int k = 0; k < i; k++) {
            y[i] -= L[i][k] * y[k];
        }
    }
    // Solve Ux = y
    Vector x(n);
    for (int i = n - 1; i >= 0; i--) {
        x[i] = y[i];
        for (int k = i + 1; k < n; k++) {
            x[i] -= U[i][k] * x[k];
        }
        x[i] /= U[i][i];
    }
    return x;
}

Vector LinearEquationSolver::jacobiMethod(double tolerance, int maxIterations) {
    // Implementation remains the same
    int n = A.size();
    Vector x(n, 0.0);
    Vector xOld(n, 0.0);

    int iteration = 0;
    while (iteration < maxIterations) {
        for (int i = 0; i < n; i++) {
            double sum = b[i];
            for (int j = 0; j < n; j++) {
                if (j != i) {
                    sum -= A[i][j] * xOld[j];
                }
            }
            x[i] = sum / A[i][i];
        }
        // Check for convergence
        double error = 0.0;
        for (int i = 0; i < n; i++) {
            error += fabs(x[i] - xOld[i]);
        }
        if (error < tolerance) break;
            xOld = x;
            iteration++;
    }
    return x;
}

Vector LinearEquationSolver::gaussSeidelMethod(double tolerance, int maxIterations) {
    // Implementation remains the same
    int n = A.size();
    Vector x(n, 0.0);

    int iteration = 0;
    while (iteration < maxIterations) {
        Vector xOld = x; // Make a copy of the current x
        for (int i = 0; i < n; i++) {
            double sum = b[i];
            for (int j = 0; j < n; j++) {
                if (j != i) {
                    sum -= A[i][j] * x[j];
                }
            }
            x[i] = sum / A[i][i];
        }

        // Check for convergence
        double error = 0.0;
        for (int i = 0; i < n; i++) {
            double sum = b[i];
            for (int j = 0; j < n; j++) {
                if (j != i) {
                    sum -= A[i][j] * x[j];
                }
            }
            double new_x = sum / A[i][i];
            error += fabs(new_x - xOld[i]);
            x[i] = new_x;
        }
        if (error < tolerance) break;
            iteration++;
    }
    return x;
}
