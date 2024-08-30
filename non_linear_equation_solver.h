#pragma once
#include <functional>
using namespace std;

class NonLinearEquationSolver {
public:
    NonLinearEquationSolver(function<double(double)> func, function<double(double)> deriv = nullptr);
    double solve(int method_choice);

private:
    function<double(double)> f;
    function<double(double)> f_prime;

    double bisectionMethod(double a, double b, double tolerance = 1e-6);
    double newtonRaphsonMethod(double initialGuess, double tolerance = 1e-6);
    double secantMethod(double x0, double x1, double tolerance = 1e-6);
    double fixedPointIteration(double initialGuess = 0.5, double tolerance = 1e-6);
};