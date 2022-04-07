#include "log.hpp"

DebugLogger::~DebugLogger() {
    file << "Closing file" << std::endl;
    file.close();
}

DebugLogger::DebugLogger(std::string path) : file(path, std::ios::app | std::ios::out) {
    if (!file.is_open()) {
        throw std::exception();
    }
}

void DebugLogger::initialize(std::string path_to_log_file) {
    if (!instance) instance = std::shared_ptr<DebugLogger>(new DebugLogger(path_to_log_file));
}

std::ostream& DebugLogger::getLogStream() {
    return file << "[INFO] ";
}
std::ostream& DebugLogger::getErrorStream() {
    return file << "[ERROR] ";
}
