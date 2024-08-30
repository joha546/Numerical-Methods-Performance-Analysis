#include "non_linear_equation_solver.h"
#include <iostream>
#include <stdexcept>
#include <cmath>
using namespace std;
#define EPSILON 1e-6


NonLinearEquationSolver::NonLinearEquationSolver(function<double(double)> func, function<double(double)> deriv): f(func), f_prime(deriv){}

double NonLinearEquationSolver::solve(int method_choice){
    double root = 0.0;

    switch (method_choice){
    case 1:
        double a, b;
        cout<<".......Bisection Method......"<<endl;
        cout << "Enter a: ";
        cin >> a;
        cout << "Enter b: ";
        cin >> b;
        root = bisectionMethod(a, b);
        cout << "Root using Bisection Method: ";
        break;
    case 2:
        double initialGuess;
        cout<<".......Newton Raphson Method......"<<endl;
        cout << "Enter Initial Guess: ";
        cin >> initialGuess;
        root = newtonRaphsonMethod(initialGuess);
        cout << "Root using Newton-Raphson Method: ";
        break;
    case 3:
        double x0, x1;
        cout<<".......Secant Method......"<<endl;
        cout << "Enter x1 :";
        cin >> x0;
        cout << "Enter x2: ";
        cin >> x1;
        root = secantMethod(x0, x1);
        cout << "Root using Secant Method: ";
        break;
    case 4:
        cout<<".......Fixed Point Iteration Method......"<<endl;
        float guess;
        cout<<"Enter Initial Guess: ";
        cin>>guess;
        root = fixedPointIteration(guess);
        cout << "Root using Fixed Point Iteration: ";
        break;
    default:
        cout << "Invalid method choice.\n";
        return 0.0;
    }
    return root;
}

double NonLinearEquationSolver::bisectionMethod(double a, double b, double tolerance){
    
    double c=a;
    if(f(a) * f(b) >= 0){
        cout<< "You haven't assumed right a and b. Please Try again.."<<endl;
        return 1;
    }
    while((b-a) >= EPSILON){
        c = (a + b)/2;
        if (f(c)==0.0){
            break;
        }
        else if(f(c) * f(a) < 0){
            b = c;
        }
        else{
            a = c;
        }
    }
    return c;
}

double NonLinearEquationSolver::newtonRaphsonMethod(double initialGuess, double tolerance){
    
    double x = initialGuess;
    while(fabs(f(x)) > tolerance){
        if(!f_prime){
            cerr << "Derivative function required for Newton-Raphson method.\n";
            return x;
        }
        double h = f(x) / f_prime(x);
        x = x - h;
    }
    return x;
}

double NonLinearEquationSolver::secantMethod(double x0, double x1, double tolerance){
    
    double x2;
    while(fabs(x1 - x0) > tolerance){
        x2 = x1 - f(x1) * (x1 - x0) / (f(x1) - f(x0));
        x0 = x1;
        x1 = x2;
    }
    return x2;
}

double NonLinearEquationSolver::fixedPointIteration(double initialGuess, double tolerance){
    
    auto g = [this](double x){ 
        return x - f(x);
    };
    double x = initialGuess;
    while (fabs(f(x)) > tolerance){
        x = g(x);
    }
    return x;
}