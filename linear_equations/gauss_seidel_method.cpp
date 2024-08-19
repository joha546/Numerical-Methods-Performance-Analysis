#include <vector>
#include <cmath>
using namespace std;

vector<double> gaussSeidelMethod(vector<vector<double>>& A, vector<double>& b, double tolerance, int maxIterations) {
    int n = A.size();
    vector<double> x(n, 0);
    int iterations = 0;

    while (iterations < maxIterations) {
        double error = 0;
        for (int i = 0; i < n; i++) {
            double sum = 0;
            for (int j = 0; j < n; j++) {
                if (i != j) {
                    sum += A[i][j] * x[j];
                }
            }
            double x_new = (b[i] - sum) / A[i][i];
            error += abs(x_new - x[i]);
            x[i] = x_new;
        }

        if (error < tolerance) {
            break;
        }

        iterations++;
    }

    return x;
}