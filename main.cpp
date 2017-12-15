#include "IO.h"
#include "Calculator.h"

int main() {
    // attempt to read input data
    IO io;
    Parameter &params = io.read();

    // calculate on input data
    Calculator calculator(params);
    std::vector<double> results = calculator.calc();

    // attempt to write results
    bool write_success = io.write(results);

    // final message
    std::cout << "Calculations were successful!" << std::endl;
    if (write_success) std::cout << "Results written to OUTPUT.txt" << std::endl;
    return EXIT_SUCCESS;
}