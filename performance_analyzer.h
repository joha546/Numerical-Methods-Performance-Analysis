// performance_analyzer.h
#pragma once
#include <chrono>
using namespace std;

template<typename Func>
double measureExecutionTime(Func func){
    auto start = chrono::high_resolution_clock::now();
    func();
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double, milli> duration = end - start;
    return duration.count();
}