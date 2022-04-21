#include "log.hpp"

ServerLogger::~ServerLogger() {
    stream << "Closing log" << std::endl;
    stream.close();
    device.close();
    file.close();
}

ServerLogger::ServerLogger(const std::string& path)
        : file(path, std::ios::app | std::ios::out), device(std::cout, file), stream(device) {
    if (!file.is_open()) {
        throw std::exception();
    }
}

void ServerLogger::initialize(const std::string& path_to_log_file) {
    if (!instance) instance = std::shared_ptr<ServerLogger>(new ServerLogger(path_to_log_file));
}

std::ostream& ServerLogger::getLogStream() {
    return stream << "[INFO] ";
}
std::ostream& ServerLogger::getErrorStream() {
    return stream << "[ERROR] ";
}
