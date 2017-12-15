#pragma once

#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>
#include <cmath>
#include <memory>
#include <limits>

struct Parameter {
    const double D{1.0 * pow(10, -8)};
    const int model_length{10};
    double model_time;
    double delta_t;
    double delta_x;
};

class IO {

public:
    Parameter &read();
    bool write(const std::vector<double> &);

private:
    Parameter params;
    double read_val(const std::vector<std::string> &, const std::string &);
};
