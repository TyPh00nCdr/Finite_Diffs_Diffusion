#include "IO.h"

Parameter &IO::read() {

    std::ifstream file("./INPUT.txt");
    // Fall-back for dev environment where executable is being compiled into a subfolder.
    if (!file.good()) {
        file.close();
        file.open("../INPUT.txt");
    }

    std::string str;
    std::vector<std::string> input_file = std::vector<std::string>();
    if (file.is_open()) {
        while (std::getline(file, str)) {
            input_file.push_back(str);
        }
        file.close();
    } else {
        std::cerr << "Unable to open INPUT.txt!" << std::endl;
        exit(EXIT_FAILURE);
    }

    try {
        params.delta_t = read_val(input_file, "Zeitschrittlaengen");
        params.delta_x = read_val(input_file, "Raumdiskretisierung");
        params.model_time = read_val(input_file, "Modellzeit");
    } catch (const std::invalid_argument &ia) {
        std::cerr << "Malformed INPUT.txt not adhering to template: " << std::endl
                  << "Zeitschrittlaengen = <number>" << std::endl
                  << "Raumdiskretisierung = <number>" << std::endl
                  << "Modellzeit = <number>" << std::endl << std::endl
                  << "(Unable to parse argument: " << ia.what() << ")" << std::endl << std::endl;
        exit(EXIT_FAILURE);
    }


    return params;
}

bool IO::write(const std::vector<double> &data) {
    std::ofstream file("./OUTPUT.csv", std::ios::trunc);
    if (file.is_open()) {
        for (int i = 0; i < data.size(); ++i) {
            file << "C(" << (i + 1) << ")," << data[i] << std::endl;
        }
        file.close();
        return true;
    } else {
        std::cerr << "Unable to write OUTPUT.csv!" << std::endl << std::endl;
        return false;
    }
}

double IO::read_val(const std::vector<std::string> &vector, const std::string &val_name) {
    auto index{std::distance(vector.begin(), std::find_if(vector.begin(), vector.end(), [&](std::string str) {
        return str.find(val_name) != std::string::npos;
    }))};

    std::string val_string = vector[index].substr(vector[index].find('=') + 1, vector[index].size());

    return std::stod(val_string);
}
