#include <functional>
#include<stdexcept>
#include <cmath>
using namespace std;

double bisectionMethod(std::function<double(double)> f, double a, double b, double tolerance, int maxIterations) {
    if (f(a) * f(b) >= 0) {
        throw std::runtime_error("Function values at endpoints must have opposite signs");
    }

    double c;
    for (int i = 0; i < maxIterations; i++) {
        c = (a + b) / 2;
        if (std::abs(f(c)) < tolerance) {
            return c;
        }
        if (f(c) * f(a) < 0) {
            b = c;
        } else {
            a = c;
        }
    }

    return c;
}