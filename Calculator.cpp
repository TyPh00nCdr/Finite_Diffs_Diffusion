#include "Calculator.h"

std::vector<double> Calculator::calc() {

    params.delta_t = determine_viable_t();
    res_size = local_discretization();
    return diffusion();
}

double Calculator::determine_viable_t() {
    double max_viable_t{pow(params.delta_x, 2) / (2 * params.D)};
    double result{params.delta_t};
    if (params.delta_t <= max_viable_t) {
        std::cerr << "Ill-formed Delta-X = " << params.delta_t << std::endl << "Delta-X should not be greater than "
                  << max_viable_t << std::endl << std::endl;
        std::string user_input{};
        do {
            std::cerr << "Continue anyway? (Y/N)    (N: Proceed with Delta-X = "
                      << max_viable_t << ")" << std::endl;
            std::cin >> user_input;
        } while (user_input.compare("Y") != 0 &&
                 user_input.compare("y") != 0 &&
                 user_input.compare("N") != 0 &&
                 user_input.compare("n") != 0);
        result = (user_input.compare("Y") == 0 || user_input.compare("y")) ? result : max_viable_t;
    }
    return result;
}

std::size_t Calculator::local_discretization() {
    // Check if the input val for Delta-X abides by the text->double->text threshold.
    // If so, we're computing on negligible rounding differences. Else, we can't properly discretize with it.
    if (fmod(params.model_length, params.delta_x) > pow(0.1, std::numeric_limits<double>::digits10)) {
        std::cerr << "Unable to discretize with Delta-X = " << params.delta_x << std::endl;
        exit(EXIT_FAILURE);
    }

    double result = params.model_length / params.delta_x + 1;

    if (SIZE_MAX < result) {
        std::cerr << "Discretization too large with Delta-X = " << params.delta_x << std::endl;
        exit(EXIT_FAILURE);
    }
    if (result < 1) {
        std::cerr << "Discretization too small with Delta-X = " << params.delta_x << std::endl;
        exit(EXIT_FAILURE);
    }

    return (std::size_t) result;
}

std::vector<double> Calculator::diffusion() {
    std::vector<double> C(res_size, 0.0);
    C[0] = 10;
    C[C.size() - 1] = 0;

    for (int n{1}; n <= params.model_time; n += params.delta_t) {
        std::vector<double> C_n(C);
        for (int j{1}; j < C.size() - 1; ++j)
            C[j] = params.D * params.delta_t * ((C_n[j + 1] - 2 * C_n[n] + C_n[n - 1]) / pow(params.delta_x, 2)) -
                   C_n[j];
    }

    return C;
}