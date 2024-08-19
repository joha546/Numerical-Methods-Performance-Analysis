#ifndef NUMERICAL_METHODS_H
#define NUMERICAL_METHODS_H

#include <vector>
#include <functional>

// Linear equation solvers
std::vector<double> gaussianElimination(std::vector<std::vector<double>>& A, std::vector<double>& b);
void luDecomposition(std::vector<std::vector<double>>& A, std::vector<std::vector<double>>& L, std::vector<std::vector<double>>& U);
std::vector<double> solveLU(std::vector<std::vector<double>>& L, std::vector<std::vector<double>>& U, std::vector<double>& b);
std::vector<double> jacobiMethod(std::vector<std::vector<double>>& A, std::vector<double>& b, double tolerance, int maxIterations);
std::vector<double> gaussSeidelMethod(std::vector<std::vector<double>>& A, std::vector<double>& b, double tolerance, int maxIterations);

// Non-linear equation solvers
double bisectionMethod(std::function<double(double)> f, double a, double b, double tolerance, int maxIterations);
double newtonRaphsonMethod(std::function<double(double)> f, std::function<double(double)> df, double x0, double tolerance, int maxIterations);
double secantMethod(std::function<double(double)> f, double x0, double x1, double tolerance, int maxIterations);
double fixedPointIteration(std::function<double(double)> g, double x0, double tolerance, int maxIterations);

// Utility functions
std::vector<double> matrixVectorMultiply(const std::vector<std::vector<double>>& A, const std::vector<double>& x);
double vectorDotProduct(const std::vector<double>& a, const std::vector<double>& b);

// Parsing functions
std::vector<std::vector<double>> parseLinearEquation(int numEquations);
std::pair<std::function<double(double)>, std::function<double(double)>> parseNonLinearEquation();

#endif // NUMERICAL_METHODS_H