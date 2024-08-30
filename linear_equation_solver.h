#pragma once
#include <vector>
using namespace std;

typedef vector<vector<double>> Matrix;
typedef vector<double> Vector;

class LinearEquationSolver {
public:
    LinearEquationSolver(Matrix A, Vector b);
    Vector solve(int method_choice);

private:
    Matrix A;
    Vector b;

    Vector gaussianElimination();
    Vector luDecomposition();
    Vector jacobiMethod(double tolerance = 1e-10, int maxIterations = 1000);
    Vector gaussSeidelMethod(double tolerance = 1e-10, int maxIterations = 1000);
};