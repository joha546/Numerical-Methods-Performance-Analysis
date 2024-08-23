#pragma once
#include <vector>
#include <functional>
#include <string>
using namespace std;

typedef vector<vector<double>> Matrix;
typedef vector<double> Vector;

class Utils {
public:
    static Matrix inputMatrix(int n);
    static Vector inputVector(int n);

    static function<double(double)> parseEquation(const string &equation);
    static function<double(double)> parseDerivative(const string &equation);

private:
    static double evaluateTerm(const string& pTerm, double val);
    static double derivativeTerm(const string& pTerm, double val);
    static double evaluatePolynomial(const string& poly, double val);
    static double evaluateDerivative(const string& poly, double val);
};

