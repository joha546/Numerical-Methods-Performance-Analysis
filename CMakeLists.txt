cmake_minimum_required(VERSION 3.10)

project(NumericalMethods)

set(CMAKE_CXX_STANDARD 17)

add_executable(NumericalMethods
    main.cpp
    linear_equation_solver.cpp
    non_linear_equation_solver.cpp
    utils.cpp
    performance_analyzer.cpp
)
