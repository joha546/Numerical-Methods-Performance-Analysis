#include <functional>
#include <cmath>
using namespace std;

double fixedPointIteration(function<double(double)> g, double x0, double tolerance, int maxIterations) {
    double x = x0;
    for (int i = 0; i < maxIterations; i++) {
        double x_new = g(x);
        if (abs(x_new - x) < tolerance) {
            return x_new;
        }
        x = x_new;
    }
    return x;
}