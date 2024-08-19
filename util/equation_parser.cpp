#include<bits/stdc++.h>
#include <string>
#include <vector>
#include <sstream>
#include <stdexcept>
#include <map>
#include <cmath>
using namespace std;

vector<vector<double>> parseLinearEquation(int numEquations) {
    vector<vector<double>> result(numEquations, vector<double>(numEquations + 1, 0));
    map<char, int> variableMap;

    for (int i = 0; i < numEquations; ++i) {
        string equation;
        cout << "Enter equation " << i + 1 << " (e.g., 2x + 3y - z = 5): ";
        cin.ignore();
        getline(cin, equation);

        istringstream iss(equation);
        string term;
        bool isLeftSide = true;
        double rightSide = 0;

        while (iss >> term) {
            if (term == "=") {
                isLeftSide = false;
                continue;
            }

            double coefficient = 1.0;
            char variable = 'x';
            bool isNegative = false;

            if (term[0] == '-') {
                isNegative = true;
                term = term.substr(1);
            } else if (term[0] == '+') {
                term = term.substr(1);
            }

            size_t varPos = term.find_first_of("abcdefghijklmnopqrstuvwxyz");
            if (varPos != string::npos) {
                variable = term[varPos];
                if (varPos > 0) {
                    coefficient = stod(term.substr(0, varPos));
                }
            } else {
                coefficient = stod(term);
            }

            if (isNegative) coefficient = -coefficient;

            if (isLeftSide) {
                if (variableMap.find(variable) == variableMap.end()) {
                    variableMap[variable] = variableMap.size();
                }
                result[i][variableMap[variable]] += coefficient;
            } else {
                rightSide += coefficient;
            }
        }
        result[i][numEquations] = rightSide;
    }

    return result;
}