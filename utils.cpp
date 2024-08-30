#include "utils.h"
#include <iostream>
#include <sstream>
#include <cmath>
using namespace std;

Matrix Utils::inputMatrix(int n){
    Matrix A(n, Vector(n));
    cout << "Enter the matrix A (row-wise):"<<endl;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            cin >> A[i][j];
        }
    }
    return A;
}

Vector Utils::inputVector(int n){
    Vector b(n);
    cout << "Enter the vector b: "<<endl;
    for (int i = 0; i < n; i++){
        cin >> b[i];
    }
    return b;
}

function<double(double)> Utils::parseEquation(const string &equation){
    return [equation](double x){
        return evaluatePolynomial(equation, x);
    };
}

function<double(double)> Utils::parseDerivative(const string &equation){
    return [equation](double x){
        return evaluateDerivative(equation, x);
    };
}

double Utils::evaluateTerm(const string& pTerm, double val){
    // Implementation to evaluate a term of equation by value....

    string coeffStr = "1";
    string powStr = "1";
    size_t xPos = pTerm.find('x');

    if (xPos != string::npos){
        if (xPos > 0) coeffStr = pTerm.substr(0, xPos);
        if (xPos + 1 < pTerm.length() && pTerm[xPos + 1] == '^'){
            powStr = pTerm.substr(xPos + 2);
        }
    }
    else{
        coeffStr = pTerm;
        powStr = "0";
    }

    double coeff = (coeffStr == "-") ? -1 : (coeffStr.empty() ? 1 : stod(coeffStr));
    double power = stod(powStr);

    return coeff * pow(val, power);
}

double Utils::derivativeTerm(const string& pTerm, double val){
    // Implementation for derivative term...

    string coeffStr = "1";
    string powStr = "1";
    size_t xPos = pTerm.find('x');

    if(xPos != string::npos){
        if(xPos > 0) coeffStr = pTerm.substr(0, xPos);
        if(xPos + 1 < pTerm.length() && pTerm[xPos + 1] == '^'){
            powStr = pTerm.substr(xPos + 2);
        }
    }
    else{
        return 0.0; // Constant term, derivative is 0
    }
    double coeff = (coeffStr == "-") ? -1 : (coeffStr.empty() ? 1 : stod(coeffStr));
    double power = stod(powStr);

    return coeff * power * pow(val, power - 1);
}

double Utils::evaluatePolynomial(const string& poly, double val){
    // Implementation to evaluate Polynomial....

    double polyValue = 0.0;
    istringstream is(poly);
    string term;
    char op = '+';

    while(is >> term){
        if (term == "+" || term == "-"){
            op = term[0];
            continue;
        }
        double termValue = evaluateTerm(term, val);
        polyValue += (op == '+') ? termValue : -termValue;
    }
    return polyValue;
}

double Utils::evaluateDerivative(const string& poly, double val){
    
    double derivativeValue = 0.0;
    istringstream is(poly);
    string term;
    char op = '+';

    while(is >> term){
        if (term == "+" || term == "-"){
            op = term[0];
            continue;
        }
        double termValue = derivativeTerm(term, val);
        derivativeValue += (op == '+') ? termValue : -termValue;
    }
    return derivativeValue;
}

