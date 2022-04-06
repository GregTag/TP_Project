#include "log.hpp"

DebugLogger::DebugLogger(std::string path) : file(path) {}

void DebugLogger::initialize(std::string path_to_log_file) {
    if (!instance) instance = std::shared_ptr<DebugLogger>(new DebugLogger(path_to_log_file));
}

std::ostream& DebugLogger::getLogStream() {
    return file << "[INFO] ";
}
std::ostream& DebugLogger::getErrorStream() {
    return file << "[ERROR] ";
}
