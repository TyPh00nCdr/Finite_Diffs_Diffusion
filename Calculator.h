#pragma once

#include <cmath>
#include <vector>
#include <limits>
#include <cstddef>
#include "IO.h"


class Calculator {
public:
    Calculator(Parameter &params) : params(params) {};
    std::vector<double> calc();

private:
    Parameter params;
    std::size_t res_size;
    double determine_viable_t();
    std::size_t local_discretization();
    std::vector<double> diffusion();
};
