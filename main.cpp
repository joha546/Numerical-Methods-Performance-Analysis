#include <iostream>
#include <chrono>
#include <iomanip>
#include <functional>
#include "numerical_methods.h"

void solveLinearEquation() {
    int n;
    std::cout << "Enter the number of equations: ";
    std::cin >> n;

    auto equation = parseLinearEquation(n);

    std::vector<std::vector<double>> A(n, std::vector<double>(n));
    std::vector<double> b(n);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            A[i][j] = equation[i][j];
        }
        b[i] = equation[i][n];
    }

    // Performance analysis
    auto measurePerformance = [&](const std::string& method, auto func) {
        auto start = std::chrono::high_resolution_clock::now();
        auto result = func();
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

        std::cout << std::setw(20) << std::left << method 
                  << std::setw(15) << std::right << duration << " microseconds\n";

        return result;
    };

    std::cout << "\nPerformance Analysis:\n";
    std::cout << std::string(40, '-') << "\n";
    std::cout << std::setw(20) << std::left << "Method" 
              << std::setw(15) << std::right << "Time (μs)\n";
    std::cout << std::string(40, '-') << "\n";

    auto x_gaussian = measurePerformance("Gaussian Elimination", [&]() { return gaussianElimination(A, b); });
    
    std::vector<std::vector<double>> L, U;
    measurePerformance("LU Decomposition", [&]() { luDecomposition(A, L, U); return std::vector<double>(); });
    auto x_lu = measurePerformance("LU Solve", [&]() { return solveLU(L, U, b); });
    
    auto x_jacobi = measurePerformance("Jacobi Method", [&]() { return jacobiMethod(A, b, 1e-6, 100); });
    auto x_gauss_seidel = measurePerformance("Gauss-Seidel", [&]() { return gaussSeidelMethod(A, b, 1e-6, 100); });

    std::cout << "\nSolution:\n";
    for (int i = 0; i < n; i++) {
        std::cout << "x[" << i << "] = " << x_gaussian[i] << "\n";
    }
}

void solveNonLinearEquation() {
    auto [f, df] = parseNonLinearEquation();

    double a, b, x0, x1;
    std::cout << "Enter interval [a, b] for Bisection method: ";
    std::cin >> a >> b;
    std::cout << "Enter initial guesses x0 and x1 for other methods: ";
    std::cin >> x0 >> x1;

    double tolerance = 1e-6;
    int maxIterations = 100;

    // Performance analysis
    auto measurePerformance = [&](const std::string& method, auto func) {
        auto start = std::chrono::high_resolution_clock::now();
        auto result = func();
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

        std::cout << std::setw(20) << std::left << method 
                  << std::setw(15) << std::right << duration << " microseconds"
                  << std::setw(15) << std::right << result << "\n";

        return result;
    };

    std::cout << "\nPerformance Analysis:\n";
    std::cout << std::string(55, '-') << "\n";
    std::cout << std::setw(20) << std::left << "Method" 
              << std::setw(15) << std::right << "Time (μs)"
              << std::setw(15) << std::right << "Root\n";
    std::cout << std::string(55, '-') << "\n";

    measurePerformance("Bisection", [&]() { return bisectionMethod(f, a, b, tolerance, maxIterations); });
    measurePerformance("Newton-Raphson", [&]() { return newtonRaphsonMethod(f, df, x0, tolerance, maxIterations); });
    measurePerformance("Secant", [&]() { return secantMethod(f, x0, x1, tolerance, maxIterations); });
    measurePerformance("Fixed Point", [&]() { return fixedPointIteration([&](double x) { return f(x) + x; }, x0, tolerance, maxIterations); });
}

int main() {
    char choice;
    
    while (true) {
        std::cout << "\nChoose equation type:\n";
        std::cout << "1. Linear Equations\n";
        std::cout << "2. Non-linear Equation\n";
        std::cout << "3. Exit\n";
        std::cout << "Enter your choice (1-3): ";
        std::cin >> choice;

        switch (choice) {
            case '1':
                solveLinearEquation();
                break;
            case '2':
                solveNonLinearEquation();
                break;
            case '3':
                std::cout << "Exiting program. Goodbye!\n";
                return 0;
            default:
                std::cout << "Invalid choice. Please try again.\n";
        }
    }

    return 0;
}