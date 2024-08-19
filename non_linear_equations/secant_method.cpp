#include <functional>
#include <cmath>
#include<stdexcept>
using namespace std;


double secantMethod(std::function<double(double)> f, double x0, double x1, double tolerance, int maxIterations) {
    double x2;
    for (int i = 0; i < maxIterations; i++) {
        double fx0 = f(x0);
        double fx1 = f(x1);
        if (std::abs(fx1 - fx0) < 1e-10) {
            throw std::runtime_error("Division by zero");
        }
        x2 = x1 - fx1 * (x1 - x0) / (fx1 - fx0);
        if (std::abs(x2 - x1) < tolerance) {
            return x2;
        }
        x0 = x1;
        x1 = x2;
    }
    return x2;
}