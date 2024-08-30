#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include "linear_equation_solver.h"
#include "non_linear_equation_solver.h"
#include "utils.h"
#include "performance_analyzer.h"
using namespace std;

int main(){
    int choice;
    cout << "Select the type of equation:\n";
    cout << "1. Non-Linear Equation\n";
    cout << "2. Linear Equation\n";
    cin >> choice;

    if(choice == 1){
        string equation;
        cout << "Enter the polynomial equation (e.g., 2x^2 + 3x + 1): "<<endl;
        cin.ignore();
        getline(cin, equation);

        try{
            auto f=Utils::parseEquation(equation);
            auto f_prime=Utils::parseDerivative(equation);

            NonLinearEquationSolver solver(f, f_prime);

            vector<string> Names={"Bisection Method", "Newton-Raphson Method", "Secant Method", "Fixed Point Iteration" };

            for(int m_Choice = 1; m_Choice <= Names.size(); ++m_Choice){
                double result;
                double executionTime = measureExecutionTime([&]() {
                    result = solver.solve(m_Choice);
                });

                cout << fixed << setprecision(6);
                cout << "Method: " << Names[m_Choice - 1] << "\n";
                cout << "Root: " << result << "\n";
                cout << "Time taken: " << executionTime << " ms\n\n";
            }
        }
        catch(const exception& e){
            cerr<< "An error occurred: "<<e.what() << endl;
        }
    }
    else if(choice == 2){
        int n;
        cout<<"Enter the size of the matrix (n x n):\n";
        cin >> n;
        Matrix A = Utils::inputMatrix(n);
        Vector b = Utils::inputVector(n);

        LinearEquationSolver solver(A,b);

        vector<string> Names={ "Gaussian Elimination", "LU Decomposition", "Jacobi Method", "Gauss-Seidel Method" };

        for(int m_Choice = 1; m_Choice<=4; ++m_Choice){
            Vector solution;
            double executionTime = measureExecutionTime([&](){
                solution = solver.solve(m_Choice);
            });

            cout<<"Method: "<<Names[m_Choice - 1] <<endl;
            cout << "Solution:"<<endl;
            for(size_t i = 0; i < solution.size(); ++i){
                cout << "x[" << i << "] = " << fixed << setprecision(6) << solution[i] <<endl;
            }
            cout << "Time taken: " << executionTime << " ms"<<endl;
        }
    }
    else{
        cout<<"Invalid choice.\n";
    }
    return 0;
}