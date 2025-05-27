#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>   
#include <stdexcept>    
#include <cerrno>     
#include <cstring>      


std::string get_env_variable(const std::string& var_name) {
    const char* val = std::getenv(var_name.c_str());
    if (!val) {
        throw std::runtime_error("Environment variable '" + var_name + "' is not set.");
    }
    return std::string(val);
}

int main(int argc, char* argv[]) {
    std::string log_path;

    try {
        if (argc > 1) {
            log_path = argv[1];
        } else {
            log_path = get_env_variable("LOG_PATH");
        }
    } catch (const std::exception& e) {
        std::cerr << "Configuration error: " << e.what() << std::endl;
        return 1;
    }

    std::ofstream log_file(log_path, std::ios::app);
    if (!log_file.is_open()) {
        std::cerr << "Error opening log file '" << log_path << "': "
                  << std::strerror(errno) << std::endl;
        return 1;
    }

    log_file << std::unitbuf;

    std::string line;
    while (std::getline(std::cin, line)) {
        log_file << line << std::endl;
        if (!log_file) {
            std::cerr << "Error writing to log file." << std::endl;
            return 1;
        }
    }

    return 0;
}
