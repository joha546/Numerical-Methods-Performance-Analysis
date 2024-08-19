#include <vector>
#include <cmath>
using namespace std;


vector<double> jacobiMethod(vector<vector<double>>& A, vector<double>& b, double tolerance, int maxIterations) {
    int n = A.size();
    vector<double> x(n, 0), x_new(n);
    int iterations = 0;

    while (iterations < maxIterations) {
        for (int i = 0; i < n; i++) {
            double sum = 0;
            for (int j = 0; j < n; j++) {
                if (i != j) {
                    sum += A[i][j] * x[j];
                }
            }
            x_new[i] = (b[i] - sum) / A[i][i];
        }

        double error = 0;
        for (int i = 0; i < n; i++) {
            error += abs(x_new[i] - x[i]);
        }

        if (error < tolerance) {
            break;
        }

        x = x_new;
        iterations++;
    }
    return x;
}