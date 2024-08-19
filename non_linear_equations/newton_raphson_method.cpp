#include <functional>
#include <cmath>
#include<stdexcept>
using namespace std;

double newtonRaphsonMethod(function<double(double)> f, function<double(double)> df, double x0, double tolerance, int maxIterations) {
    double x = x0;
    for (int i = 0; i < maxIterations; i++) {
        double fx = f(x);
        if (abs(fx) < tolerance) {
            return x;
        }
        double dfx = df(x);
        if (dfx == 0) {
            throw runtime_error("Derivative is zero");
        }
        x = x - fx / dfx;
    }
    return x;
}